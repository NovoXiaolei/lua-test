local cjson = require "cjson"
local cjson2 = cjson.new()
local cjson_safe = require "cjson.safe"

file = io.open( "package-config.json", "r" )
data = file:read("*a")
text = cjson.decode(data)
jsonstr = cjson.encode(text)
print(jsonstr)



