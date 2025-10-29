---@meta _
error("Cannot require a meta file")

lviz.gp = {}

---@class lviz.gp.Pnt
---@field x number
---@field y number
---@field z number
---@overload fun():lviz.gp.Pnt
---@overload fun(other: lviz.gp.Pnt|lviz.gp.Vec):lviz.gp.Pnt
---@overload fun(x: number, y: number, z: number):lviz.gp.Pnt
lviz.gp.Pnt = {}

---
---@return boolean
function lviz.gp.Pnt:IsUnset() end

---
---@param other lviz.gp.Pnt
---@return number
function lviz.gp.Pnt:Distance(other) end

---
---@param other lviz.gp.Pnt
---@return number
function lviz.gp.Pnt:Distance2(other) end

---
---@param other lviz.gp.Pnt|lviz.gp.Vec
---@return lviz.gp.Pnt
function lviz.gp.Pnt:Added(other) end

---
---@overload fun(self: lviz.gp.Pnt, other: lviz.gp.Pnt):lviz.gp.Vec
---@overload fun(self: lviz.gp.Pnt, other: lviz.gp.Vec):lviz.gp.Pnt
function lviz.gp.Pnt:Subtracted(...) end

---
---@param scale number
---@return lviz.gp.Pnt
function lviz.gp.Pnt:Multiplied(scale) end

---
---@param scale number
---@return lviz.gp.Pnt
function lviz.gp.Pnt:Divided(scale) end

---
---@return lviz.gp.Pnt
function lviz.gp.Pnt:Negated() end

---@class lviz.gp.Vec
---@field x number
---@field y number
---@field z number
---@overload fun():lviz.gp.Vec
---@overload fun(other: lviz.gp.Pnt|lviz.gp.Vec):lviz.gp.Vec
---@overload fun(x: number, y: number, z: number):lviz.gp.Vec
lviz.gp.Vec = {}

---
---@return boolean
function lviz.gp.Vec:IsUnset() end

---
---@return number
function lviz.gp.Vec:Magnitude() end

---
---@param other lviz.gp.Vec
---@return lviz.gp.Vec
function lviz.gp.Vec:Added(other) end

---
---@param other lviz.gp.Vec
---@return lviz.gp.Vec
function lviz.gp.Vec:Subtracted(other) end

---
---@param scale number
---@return lviz.gp.Vec
function lviz.gp.Vec:Multiplied(scale) end

---
---@param scale number
---@return lviz.gp.Vec
function lviz.gp.Vec:Divided(scale) end

---
---@return lviz.gp.Vec
function lviz.gp.Vec:Negated() end

---
---@param other lviz.gp.Vec
---@return number
function lviz.gp.Vec:Dot(other) end

---
---@param other lviz.gp.Vec
---@return lviz.gp.Vec
function lviz.gp.Vec:Crossed(other) end

---
---@param other lviz.gp.Vec
---@return number
function lviz.gp.Vec:Angle(other) end

---
---@param other lviz.gp.Vec
---@param ref lviz.gp.Vec
---@return number
function lviz.gp.Vec:AngleWithRef(other, ref) end

---@class lviz.gp.Ax1
---@overload fun():lviz.gp.Ax1
---@overload fun(location: lviz.gp.Pnt, direction: lviz.gp.Vec):lviz.gp.Ax1
lviz.gp.Ax1 = {}

---
---@return lviz.gp.Pnt
function lviz.gp.Ax1:Location() end

---
---@return lviz.gp.Vec
function lviz.gp.Ax1:Direction() end

---@class lviz.gp.Ax2
---@overload fun():lviz.gp.Ax2
---@overload fun(location: lviz.gp.Pnt, direction: lviz.gp.Vec):lviz.gp.Ax2
---@overload fun(location: lviz.gp.Pnt, x_direction: lviz.gp.Vec, y_direction: lviz.gp.Vec):lviz.gp.Ax2
lviz.gp.Ax2 = {}

---
---@return lviz.gp.Ax1
function lviz.gp.Ax2:Axis() end

---
---@return lviz.gp.Pnt
function lviz.gp.Ax2:Location() end

---
---@return lviz.gp.Vec
function lviz.gp.Ax2:Direction() end

---
---@return lviz.gp.Vec
function lviz.gp.Ax2:XDirection() end

---
---@return lviz.gp.Vec
function lviz.gp.Ax2:YDirection() end

---
---@param local_coord lviz.gp.Pnt
---@return lviz.gp.Pnt
function lviz.gp.Ax2:ToWorld(local_coord) end

---
---@param world_coord lviz.gp.Pnt
---@return lviz.gp.Pnt
function lviz.gp.Ax2:ToLocal(world_coord) end
