@echo off
@echo --params string: %1 %2 %3
@echo --param 1: %1
@echo --param 2: %2
@echo --param 3: %3
SET /a res1 = %1 + %2
SET /a res2 = %1 * %2
SET /a res3 = %3 / %2
SET /a res4 = %2 - %1
SET /a res5 = %res4% * (%1 - %2)
@echo -- %1 + %2 = %res1%
@echo -- %1 * %2 = %res2%
@echo -- %3 / %2 = %res3%
@echo -- %2 - %1 = %res4%
@echo -- (%2 -%1)*(%1 - %2) = %res5%
PAUSE