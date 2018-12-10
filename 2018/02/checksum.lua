#!/usr/bin/env lua

function anyValueEquals (set, value)
	for k, v in pairs(set) do
		if v == value then return true end
	end
	return false
end

function countCharacters (line)
	local charCounts = {}
	for c in line:gmatch"." do
		charCounts[c] = 0
	end
	for c in line:gmatch"." do
		charCounts[c] = (charCounts[c] + 1)
	end
	return charCounts
end

local countThree = 0
local countTwo = 0

for line in io.lines(arg[1]) do
	local charCounts = countCharacters(line)
	if anyValueEquals(charCounts, 2) then countTwo = (countTwo + 1) end
	if anyValueEquals(charCounts, 3) then countThree = (countThree + 1) end
end

print (countThree * countTwo)
