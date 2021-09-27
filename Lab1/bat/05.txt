@echo off
@echo -- params string: %1 %2 %3
@echo -- param 1: %1
@echo -- param 2: %2
@echo -- param 3: %3
SET /a res = %1 %3 %2
@echo result: %res%