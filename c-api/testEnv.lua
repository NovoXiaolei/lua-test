require 'testenv'
local fun1 = function()
    local var = 'Hello world'
    testenv.setValue(var)
    print(testevn.getValue())
end

fun1()
