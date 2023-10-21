#include <clang_driver.h>

const char * ClangDriver::default_format_style = "--style=\
{ \
  BraceWrapping: { \
    AfterCaseLabel: false, \
    AfterClass: false, \
    AfterControlStatement: Never \
  }, \
  IndentWidth: 4, \
  AllowShortBlocksOnASingleLine: Empty, \
  AllowShortEnumsOnASingleLine: true, \
  AllowShortCaseLabelsOnASingleLine: true, \
  AllowShortFunctionsOnASingleLine: Empty, \
  AlwaysBreakAfterReturnType: None, \
  AlwaysBreakTemplateDeclarations: Yes, \
  BinPackArguments: true, \
  BinPackParameters: true, \
  ContinuationIndentWidth: 4, \
  BreakBeforeBinaryOperators: NonAssignment, \
  BreakBeforeTernaryOperators: true, \
  BreakConstructorInitializers: AfterColon, \
  BreakInheritanceList: AfterColon, \
  IndentAccessModifiers: true, \
  IndentCaseLabels: true, \
  IndentPPDirectives: BeforeHash, \
  LambdaBodyIndentation: Signature, \
  NamespaceIndentation: All, \
  PointerAlignment: Middle, \
  ReferenceAlignment: Middle, \
  ReflowComments: true, \
  ShortNamespaceLines: 0, \
  SortIncludes: CaseSensitive, \
  SpaceAfterCStyleCast: true, \
  SpaceAfterLogicalNot: false, \
  SpaceAfterTemplateKeyword: true, \
  SpaceBeforeAssignmentOperators: true, \
  SpaceBeforeCaseColon: false, \
  SpaceBeforeCpp11BracedList: true, \
  SpaceBeforeCtorInitializerColon: true, \
  SpaceBeforeInheritanceColon: true, \
  SpaceBeforeParens: ControlStatements, \
  SpaceBeforeRangeBasedForLoopColon: true, \
  SpaceBeforeSquareBrackets: false, \
  SpaceInEmptyBlock: false, \
  SpaceInEmptyParentheses: false, \
  SpacesInLineCommentPrefix: { \
    Minimum: 1, \
    Maximum: -1 \
  }, \
  TabWidth: 4, \
  UseTab: Never \
} \
";
