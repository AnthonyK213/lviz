---@meta _
error("Cannot require a meta file")

lviz.log = {}

---
function lviz.log.Clear() end

lviz.view3d = {}

---
---@param obj lviz.canvas.Presentable
---@return boolean
function lviz.view3d.Display(obj) end

---
function lviz.view3d.Clear() end
