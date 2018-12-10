#!/usr/bin/env lua

function difference(line1, line2)
	local diff = 0
	for i = 1, #line1 do
		if line1:sub(i, i) ~= line2:sub(i, i) then
			diff = diff + 1
		end
	end
	return diff
end

function compareLine(line1, lines)
	for i, line2 in ipairs(lines) do
		if difference(line1, line2) == 1 then
			printCommon (line1, line2)
			os.exit()
		end
	end
end

function printCommon(line1, line2)
	for i = 1, #line1 do
		if line1:sub(i, i) ~= line2:sub(i, i) then
			print (line1:sub(0,i-1)..line1:sub(i+1))
		end
	end
end

local lines = {}
for line in io.lines(arg[1]) do
	table.insert (lines, line)
end

-- O(n²) Could be faster with recursion
for i, line in ipairs(lines) do
	compareLine (line, lines)
end
