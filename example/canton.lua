lviz.ui.log.Clear()
lviz.ui.view3d.Clear()

local async = require("lviz.async.init")
local Task = require("lviz.async.Task")

local R1 = 4
local R2 = 2.4
local H = 40
local N = 24
local T = 0.38

local sector = 2 * math.pi / N
local offset = math.floor(N * T)

async.spawn(function()
  for i = 0, N - 1 do
    local a1 = sector * i
    local a2 = sector * (i + offset)
    local pnt1 = lviz.gp.Pnt(R1 * math.cos(a1), R1 * math.sin(a1), 0)
    local pnt2 = lviz.gp.Pnt(R2 * math.cos(a2), R2 * math.sin(a2), H)
    local node = lviz.canvas.Point(pnt2)
    local column = lviz.canvas.Line(pnt1, pnt2)
    lviz.ui.view3d.Display(node)
    lviz.ui.view3d.Display(column)
    async.await(Task.Delay(100))
    lviz.ui.Update()
  end

  local tip = lviz.canvas.Polyline {
    lviz.gp.Pnt(0, 0, H),
    lviz.gp.Pnt(0, 0, H * 1.3)
  }
  lviz.ui.view3d.Display(tip)

  print("Done")
end)

local sqrt3 = math.sqrt(3)
local base = lviz.canvas.Triangle(
  lviz.gp.Pnt(-sqrt3 * R1, -R1, 0),
  lviz.gp.Pnt(sqrt3 * R1, -R1, 0),
  lviz.gp.Pnt(0, 2 * R1, 0))
lviz.ui.view3d.Display(base)
