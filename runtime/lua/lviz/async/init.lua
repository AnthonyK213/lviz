local M = {}

---@class lviz.async.Awaitable
---@field await fun():any

---Spawns a new asynchronous action.
---@param action function
function M.spawn(action)
  local f = action

  local co_cur = coroutine.running()
  if co_cur then
    f = function()
      action()
      lviz.uv.new_async(function()
        coroutine.resume(co_cur)
      end):send()
    end
  end

  local co_new = coroutine.create(f)
  coroutine.resume(co_new)
end

---
---@param awaitable lviz.async.Awaitable
---@return any
function M.await(awaitable)
  return awaitable:await()
end

return M
