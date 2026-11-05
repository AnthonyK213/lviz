local M = {}

---@class lviz.async.Awaitable
---@field await fun():any

---Spawns a new asynchronous action.
---@param action function
function M.spawn(action)
  local co_new = coroutine.create(action)
  coroutine.resume(co_new)
end

---
---@param awaitable lviz.async.Awaitable
---@return any
function M.await(awaitable)
  return awaitable:await()
end

return M
