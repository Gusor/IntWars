--package.path = '../../lua/lib/?.lua;' .. package.path  -- add library folder to path
Vector2 = require 'Vector2' -- include 2d vector lib 

print("Path is " .. debug.getinfo(1).short_src)


function finishCasting()
local current = Vector2:new(getOwnerX(), getOwnerY())
local to = Vector2:new(getSpellToX(), getSpellToY())

to:sub(current)


local trueCoords

if(to:length() > 475) then

to:normalize()
local range = Vector2:Mult(to,475)
trueCoords = Vector2:Add(current, range)
else
trueCoords = Vector2:new(getSpellToX(), getSpellToY())
end
teleportTo(trueCoords.x, trueCoords.y)
print("Ezreal E from lua" ..trueCoords.x .. " " .. trueCoords.y)
end

