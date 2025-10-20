---@meta _
error("Cannot require a meta file")

lviz.appl = {}

---@class lviz.appl.Extension
lviz.appl.Extension = {}

---
---@return boolean
function lviz.appl.Extension:IsValid() end

---
---@return boolean
function lviz.appl.Extension:IsLoaded() end

---
---@return string
function lviz.appl.Extension:GetPath() end

---
---@return string
function lviz.appl.Extension:GetName() end

---
---@param name string
---@return lviz.appl.Extension
function lviz.appl.GetExtension(name) end
