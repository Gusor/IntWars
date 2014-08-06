--require "../../lib/Vector2.lua" -- include 2d vector lib 


function finishCasting()
teleportTo(500.0, 500.0)
print("Hello from lua! TELEPORT!")
print("Owner X is: " .. getOwnerX())
end