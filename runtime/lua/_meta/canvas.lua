---@meta _
error("Cannot require a meta file")

lviz.canvas = {}

---@class lviz.canvas.Object
lviz.canvas.Object = {}

---
---@return integer
function lviz.canvas.Object:GetRefCount() end

---@class lviz.canvas.Presentable : lviz.canvas.Object
lviz.canvas.Presentable = {}

---@class lviz.canvas.Geometry : lviz.canvas.Presentable
lviz.canvas.Geometry = {}

---@class lviz.canvas.Point : lviz.canvas.Geometry
---@overload fun(coord: lviz.gp.Pnt):lviz.canvas.Point
---@overload fun(x: number, y: number, z: number):lviz.canvas.Point
lviz.canvas.Point = {}

---@class lviz.canvas.Curve : lviz.canvas.Geometry
lviz.canvas.Curve = {}

---@class lviz.canvas.Circle : lviz.canvas.Curve
---@overload fun(position: lviz.gp.Ax2, radius: number):lviz.canvas.Circle
lviz.canvas.Circle = {}

---@class lviz.canvas.Ellipse : lviz.canvas.Curve
---@overload fun(position: lviz.gp.Ax2, major_radius: number, minor_radius: number):lviz.canvas.Ellipse
lviz.canvas.Ellipse = {}

---@class lviz.canvas.Line : lviz.canvas.Curve
---@overload fun(point1: lviz.gp.Pnt, point2: lviz.gp.Pnt):lviz.canvas.Line
lviz.canvas.Line = {}

---@class lviz.canvas.Polyline : lviz.canvas.Curve
---@overload fun(vertices: lviz.gp.Pnt[]):lviz.canvas.Polyline
lviz.canvas.Polyline = {}

---@class lviz.canvas.TrimmedCurve : lviz.canvas.Curve
---@overload fun(curve: lviz.canvas.Curve, t0: number, t1: number):lviz.canvas.TrimmedCurve
lviz.canvas.TrimmedCurve = {}

---@class lviz.canvas.Surface : lviz.canvas.Geometry
lviz.canvas.Surface = {}

---@class lviz.canvas.Triangle : lviz.canvas.Surface
---@overload fun(point1: lviz.gp.Pnt, point2: lviz.gp.Pnt, point3: lviz.gp.Pnt):lviz.canvas.Triangle
---@overload fun(point1: lviz.gp.Pnt, point2: lviz.gp.Pnt, point3: lviz.gp.Pnt, normal1: lviz.gp.Vec, normal2: lviz.gp.Vec, normal3: lviz.gp.Vec):lviz.canvas.Triangle
lviz.canvas.Triangle = {}
