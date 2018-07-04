local data = {
}


math.randomseed(os.time())
for i = 1, 10 do
    local cell = {}
    cell[1] = 'data'..i
    cell.points = math.random(100)
    cell.level = math.random(30)
    table.insert(data, cell)
end

local startTime  = os.time()

table.sort(data, function(a, b)
    if a.points > b.points then
        return true
    elseif a.points == b.points then
        if a.level > b.level then
            return true
        else
            return false
        end
    else
        return false
    end
end)

local user1_index = math.random(10)
local user2_index = math.random(10)
while(user2_index == user1_index)
do
    user2_index = math.random(10)
end

local user1 = data[user1_index]
local user2 = data[user2_index]


local endTime = os.time()
print('use '..(endTime - startTime))
for i = 1, 10 do
    local v= data[i]
    print(v[1]..' points '..v.points..' level '..v.level)
end
