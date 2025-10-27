---@meta _
error("Cannot require a meta file")

lviz.canvas = {}

---@class lviz.canvas.Object
lviz.canvas.Object = {}

---
---@return integer
function lviz.canvas.Object:GetRefCount() end

---@class lviz.canvas.Geometry : lviz.canvas.Object
lviz.canvas.Geometry = {}

---@class lviz.canvas.Curve : lviz.canvas.Geometry
lviz.canvas.Curve = {}

---@class lviz.canvas.Line : lviz.canvas.Curve
---@overload fun(point1: lviz.glm.vec3, point2: lviz.glm.vec3):lviz.canvas.Line
lviz.canvas.Line = {}

---@class lviz.canvas.Polyline : lviz.canvas.Curve
---@overload fun(vertices: lviz.glm.vec3[]):lviz.canvas.Polyline
lviz.canvas.Polyline = {}

---@class lviz.canvas.Surface : lviz.canvas.Geometry
lviz.canvas.Surface = {}

---@class lviz.canvas.Triangle : lviz.canvas.Surface
---@overload fun(point1: lviz.glm.vec3, point2: lviz.glm.vec3, point3: lviz.glm.vec3):lviz.canvas.Triangle
---@overload fun(point1: lviz.glm.vec3, point2: lviz.glm.vec3, point3: lviz.glm.vec3, normal1: lviz.glm.vec3, normal2: lviz.glm.vec3, normal3: lviz.glm.vec3):lviz.canvas.Triangle
lviz.canvas.Triangle = {}
