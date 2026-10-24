# General Development Rules for AI
- Project and documentation (including comments) language is English (US).
- Always do literally only what the user requested. If you think it's necessary to additionally do something that the user didn't explicitly instruct, formulate your proposal in the chat and wait for user confirmation.
- If you need additional information to solve the task, ask questions one at a time. When you're ready to formulate a solution, report this and proceed after user confirmation.
- We work with TDD in mind: first we achieve a red test, then we implement to make the test green. In one action you can change either only the test or only the implementation, depending on which stage of the Red-Green-Refactor cycle we're currently at. After the test is written and agreed upon, it can only be changed after user confirmation.
- To run tests, use `pio test -e native`.
- For instance initialization, prefer fluent setters over constructor parameters - this allows initialization to stay obvious and be done in any order.
- Adhere to Clean Code principles whenever reasonable.
- Do not use "wide" indents. E. i., with fluent interface, don't align methods when breaking the line, use just a single-tab indent (4 spaces) for each indentation level:
```cpp
// WRONG!
controller.addItem()
         ->execute(); // Don't align method names

// WRONG!
controller.addItem()
          ->execute(); // Don't align dots/arrows/etc.

// CORRECT:
controller.addItem()
    ->execute(); // Just use single tab
```
