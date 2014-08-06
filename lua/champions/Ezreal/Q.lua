Vector2 = require 'Vector2' -- include 2d vector lib 

function finishCasting()
local current = Vector2:new(getOwnerX(), getOwnerY())
local to = Vector2:new(getSpellToX(), getSpellToY())

to:sub(current)

to:normalize()
local range = Vector2:Mult(to,1150)
local trueCoords = Vector2:Add(current, range)

addProjectile(trueCoords.x, trueCoords.y ,2000)

end