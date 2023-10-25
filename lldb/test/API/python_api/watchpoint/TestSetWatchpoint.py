"""
Use lldb Python SBValue API to create a watchpoint for read_write of 'globl' var.
"""

import lldb
from lldbsuite.test.decorators import *
from lldbsuite.test.lldbtest import *
from lldbsuite.test import lldbutil


class SetWatchpointAPITestCase(TestBase):
    NO_DEBUG_INFO_TESTCASE = True

    def setUp(self):
        # Call super's setUp().
        TestBase.setUp(self)
        # Our simple source filename.
        self.source = "main.c"
        # Find the line number to break inside main().
        self.line = line_number(self.source, "// Set break point at this line.")
        self.build()

    # Read-write watchpoints not supported on SystemZ
    @expectedFailureAll(archs=["s390x"])
    def test_watch_val(self):
        """Exercise SBValue.Watch() API to set a watchpoint."""
        self._test_watch_val(variable_watchpoint=False)
        pass

    @expectedFailureAll(archs=["s390x"])
    def test_watch_variable(self):
        """
        Exercise some watchpoint APIs when the watchpoint
        is created as a variable watchpoint.
        """
        self._test_watch_val(variable_watchpoint=True)

    def _test_watch_val(self, variable_watchpoint):
        exe = self.getBuildArtifact("a.out")

        # Create a target by the debugger.
        target = self.dbg.CreateTarget(exe)
        self.assertTrue(target, VALID_TARGET)

        # Now create a breakpoint on main.c.
        breakpoint = target.BreakpointCreateByLocation(self.source, self.line)
        self.assertTrue(
            breakpoint and breakpoint.GetNumLocations() == 1, VALID_BREAKPOINT
        )

        # Now launch the process, and do not stop at the entry point.
        process = target.LaunchSimple(None, None, self.get_process_working_directory())

        # We should be stopped due to the breakpoint.  Get frame #0.
        process = target.GetProcess()
        self.assertState(process.GetState(), lldb.eStateStopped, PROCESS_STOPPED)
        thread = lldbutil.get_stopped_thread(process, lldb.eStopReasonBreakpoint)
        frame0 = thread.GetFrameAtIndex(0)

        # Watch 'global' for read and write.
        if variable_watchpoint:
            # FIXME: There should probably be an API to create a
            # variable watchpoint.
            self.runCmd("watchpoint set variable -w read_write -- global")
            watchpoint = target.GetWatchpointAtIndex(0)
            self.assertEqual(
                watchpoint.GetWatchValueKind(), lldb.eWatchPointValueKindVariable
            )
            self.assertEqual(watchpoint.GetWatchSpec(), "global")
            # Synthesize an SBValue from the watchpoint
            watchpoint_addr = lldb.SBAddress(watchpoint.GetWatchAddress(), target)
            value = target.CreateValueFromAddress(
                watchpoint.GetWatchSpec(), watchpoint_addr, watchpoint.GetType()
            )
        else:
            value = frame0.FindValue("global", lldb.eValueTypeVariableGlobal)
            error = lldb.SBError()
            watchpoint = value.Watch(True, True, True, error)
            self.assertTrue(
                value and watchpoint,
                "Successfully found the variable and set a watchpoint",
            )
            self.DebugSBValue(value)
            self.assertEqual(
                watchpoint.GetWatchValueKind(), lldb.eWatchPointValueKindExpression
            )
            # FIXME: The spec should probably be '&global' given that the kind
            # is reported as eWatchPointValueKindExpression. If the kind is
            # actually supposed to be eWatchPointValueKindVariable then the spec
            # should probably be 'global'.
            self.assertEqual(watchpoint.GetWatchSpec(), None)

        self.assertEqual(watchpoint.GetType().GetDisplayTypeName(), "int32_t")
        self.assertEqual(value.GetName(), "global")
        self.assertEqual(value.GetType(), watchpoint.GetType())
        self.assertTrue(watchpoint.IsWatchingReads())
        self.assertTrue(watchpoint.IsWatchingWrites())

        # Hide stdout if not running with '-t' option.
        if not self.TraceOn():
            self.HideStdout()

        print(watchpoint)

        # Continue.  Expect the program to stop due to the variable being
        # written to.
        process.Continue()

        if self.TraceOn():
            lldbutil.print_stacktraces(process)

        thread = lldbutil.get_stopped_thread(process, lldb.eStopReasonWatchpoint)
        self.assertTrue(thread, "The thread stopped due to watchpoint")
        self.DebugSBValue(value)

        # Continue.  Expect the program to stop due to the variable being read
        # from.
        process.Continue()

        if self.TraceOn():
            lldbutil.print_stacktraces(process)

        thread = lldbutil.get_stopped_thread(process, lldb.eStopReasonWatchpoint)
        self.assertTrue(thread, "The thread stopped due to watchpoint")
        self.DebugSBValue(value)

        # Continue the process.  We don't expect the program to be stopped
        # again.
        process.Continue()

        # At this point, the inferior process should have exited.
        self.assertEqual(process.GetState(), lldb.eStateExited, PROCESS_EXITED)

        self.dbg.DeleteTarget(target)
        self.assertFalse(watchpoint.IsValid())
