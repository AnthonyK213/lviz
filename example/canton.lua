lviz.view3d.Purge()

local R1 = 4
local R2 = 2.4
local H = 40
local N = 24
local T = 0.38

local sector = 2 * math.pi / N
local offset = math.floor(N * T)
local height = H * 0.5
for i = 0, N - 1 do
  local a1 = sector * i
  local a2 = sector * (i + offset)
  local column = lviz.canvas.Polyline {
    lviz.glm.vec3(R1 * math.cos(a1), R1 * math.sin(a1), -height),
    lviz.glm.vec3(R2 * math.cos(a2), R2 * math.sin(a2), height)
  }
  lviz.view3d.AddGeometry(column)
end

local tip = lviz.canvas.Polyline {
  lviz.glm.vec3(0, 0, height),
  lviz.glm.vec3(0, 0, height * 1.5)
}
lviz.view3d.AddGeometry(tip)

local sqrt3 = math.sqrt(3)
local base = lviz.canvas.Triangle(
  lviz.glm.vec3(-sqrt3 * R1, -R1, -height),
  lviz.glm.vec3(sqrt3 * R1, -R1, -height),
  lviz.glm.vec3(0, 2 * R1, -height))
lviz.view3d.AddGeometry(base)
