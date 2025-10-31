---@meta _
error("Cannot require a meta file")

lviz.log = {}

---
function lviz.log.Clear() end

lviz.view3d = {}

---
---@param geom lviz.canvas.Geometry
---@return boolean
function lviz.view3d.Display(geom) end

---
function lviz.view3d.Clear() end
