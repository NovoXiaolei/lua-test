--list

node = {next = nil, value}
local l = node
function addElement(newNode)
	-- body
	local itr = l
	itr.next = newNode
	itr = newNode
	print(itr.value)
end

function output()
	while l do
		print(l.value)
		l = l.next
	end
end

node1 = {next = nil, value = 1}
node2 = {next = nil, value = 2}
addElement(node1)
addElement(node2)
output()