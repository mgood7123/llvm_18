"""
Regression test for <rdar://problem/8981098>:

The expression parser's type search only looks in the current compilation unit for types.
"""


import lldb
from lldbsuite.test.decorators import *
from lldbsuite.test.lldbtest import *
from lldbsuite.test import lldbutil


class ObjCTypeQueryTestCase(TestBase):
    def setUp(self):
        # Call super's setUp().
        TestBase.setUp(self)
        # Find the line number to break for main.m.
        self.line = line_number(
            "main.m", "// Set breakpoint here, then do 'expr (NSArray*)array_token'."
        )

    @add_test_categories(["objc"])
    def test(self):
        """The expression parser's type search should be wider than the current compilation unit."""
        self.build()
        self.runCmd("file " + self.getBuildArtifact("a.out"), CURRENT_EXECUTABLE_SET)

        lldbutil.run_break_set_by_file_and_line(
            self, "main.m", self.line, num_expected_locations=1, loc_exact=True
        )

        self.runCmd("run", RUN_SUCCEEDED)

        self.runCmd("settings set target.prefer-dynamic-value no-dynamic-values")

        # Now do a NSArry type query from the 'main.m' compile uint.
        self.expect("expression (NSArray*)array_token", substrs=["(NSArray *) $0 = 0x"])
        # (NSArray *) $0 = 0x00007fff70118398
