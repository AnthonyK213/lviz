lviz.view3d.Purge()

local H = 10

local vertices = {
  lviz.glm.vec3(-H, -H, -H),
  lviz.glm.vec3(H, -H, -H),
  lviz.glm.vec3(H, H, -H),
  lviz.glm.vec3(-H, H, -H),
  lviz.glm.vec3(-H, -H, H),
  lviz.glm.vec3(H, -H, H),
  lviz.glm.vec3(H, H, H),
  lviz.glm.vec3(-H, H, H),
}

local facets = {
  { 1, 3, 2 },
  { 1, 4, 3 },
  { 1, 6, 5 },
  { 1, 2, 6 },
  { 2, 7, 6 },
  { 2, 3, 7 },
  { 3, 8, 7 },
  { 3, 4, 8 },
  { 4, 5, 8 },
  { 4, 1, 5 },
  { 5, 6, 7 },
  { 5, 7, 8 },
}

for _, facet in ipairs(facets) do
  lviz.view3d.DrawTriangle(vertices[facet[1]], vertices[facet[2]], vertices[facet[3]])
end
