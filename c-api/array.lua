local myarray = require "myarray"

--_G.package.cpath = _G.package.cpath..";./?.so"
print(_G.package.cpath)
hi = myarray.hello_c('hi c, from lua')
print(hi)
a = myarray.new(200)
print(a)
print(myarray.size(a));
--for i = 1, 1000 do
--    myarray.set(a, i, i%5 ==0)
--end
--print(data.get(a, 10))
