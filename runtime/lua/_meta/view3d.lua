---@meta _
error("Cannot require a meta file")

lviz.view3d = {}

---
---@param point lviz.glm.vec3
---@return boolean
function lviz.view3d.DrawPoint(point) end

---
---@param point1 lviz.glm.vec3
---@param point2 lviz.glm.vec3
---@return boolean
function lviz.view3d.DrawLine(point1, point2) end

---
---@overload fun(point1: lviz.glm.vec3, point2: lviz.glm.vec3, point3: lviz.glm.vec3):boolean
---@overload fun(point1: lviz.glm.vec3, point2: lviz.glm.vec3, point3: lviz.glm.vec3, normal1: lviz.glm.vec3, normal2: lviz.glm.vec3, normal3: lviz.glm.vec3):boolean
function lviz.view3d.DrawTriangle(...) end

---
function lviz.view3d.Purge() end
