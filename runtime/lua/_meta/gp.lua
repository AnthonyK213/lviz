---@meta _
error("Cannot require a meta file")

lviz.gp = {}

---@class lviz.gp.Pnt
---@overload fun():lviz.gp.Pnt
---@overload fun(x: number, y: number, z: number):lviz.gp.Pnt
lviz.gp.Pnt = {}

---@class lviz.gp.Vec
---@overload fun():lviz.gp.Vec
---@overload fun(x: number, y: number, z: number):lviz.gp.Vec
lviz.gp.Vec = {}

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
---@param x number
---@param y number
---@param z number
---@return lviz.gp.Pnt
function lviz.gp.Ax2:Evaluate(x, y, z) end
