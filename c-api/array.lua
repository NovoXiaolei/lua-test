local myarray = require "myarray"

--_G.package.cpath = _G.package.cpath..";./?.so"
print(_G.package.cpath)
hi = myarray.hello_c('hi c, from lua')
print(hi)
--a = array.new(200)
--print(a)
--print(array.size(a));
--for i = 1, 1000 do
--    array.set(a, i, i%5 ==0)
--end
--print(data.get(a, 10))
