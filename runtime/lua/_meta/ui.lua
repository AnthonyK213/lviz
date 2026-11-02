---@meta _
error("Cannot require a meta file")

lviz.ui = {}

---
function lviz.ui.Update() end

lviz.ui.log = {}

---
function lviz.ui.log.Clear() end

lviz.ui.view3d = {}

---
---@param obj lviz.canvas.Presentable
---@return boolean
function lviz.ui.view3d.Display(obj) end

---
function lviz.ui.view3d.Clear() end
