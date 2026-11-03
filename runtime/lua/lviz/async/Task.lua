local function table_pack(...)
  return { n = select("#", ...), ... }
end

---
---@param pack table
---@param i? integer
---@return ...
local function table_unpack(pack, i)
  return unpack(pack, i or 1, pack.n)
end

---
---@param pack table
---@param pos integer
---@param value any
local function table_insert(pack, pos, value)
  for i = pack.n, pos, -1 do
    pack[i + 1] = pack[i]
  end
  pack[pos] = value
  pack.n = pack.n + 1
end

---
---@param timeout number Timeout in milliseconds.
---@param fn function
local function defer_fn(timeout, fn)
  local timer = lviz.uv.new_timer()
  lviz.uv.timer_start(timer, timeout, 0, fn)
end

---@class lviz.async.Task : lviz.async.Awaitable
---@field private m_action function
---@field private m_args table
---@field private m_cb_index integer
---@field private m_cb function
---@field private m_status 0|-1|-2 Task status, 0: Created; -1: Running; -2: RanToCompletion
---@field private m_result table
---@overload fun(action:function, cb_index:integer, ...):lviz.async.Task
local Task = {}

---@private
Task.__index = Task

setmetatable(Task, {
  __call = function(task, action, cb_index, ...)
    return task.new(action, cb_index, ...)
  end
})

---@private
---Constructor.
---@param action function
---@param cb_index integer
---@param ... any
---@return lviz.async.Task
function Task.new(action, cb_index, ...)
  local task = {
    m_action = action,
    m_args = table_pack(...),
    m_cb_index = cb_index,
    m_status = 0,
  }
  setmetatable(task, Task)
  return task
end

---@private
---Starts the task.
---@return boolean
function Task:start()
  if self.m_status ~= 0 or not self.m_action or not self.m_cb_index or
      self.m_cb_index < 0 or self.m_cb_index > self.m_args.n then
    return false
  end

  local cb = function(...)
    self.m_status = -2
    if type(self.m_cb) == "function" then
      self.m_cb(...)
    end
  end

  self.m_status = -1

  local args = self.m_args
  if self.m_cb_index == 0 then
    args[args.n + 1] = cb
    args.n = args.n + 1
  else
    table_insert(args, self.m_cb_index + 0, cb)
  end

  self.m_action(table_unpack(args))

  return true
end

---@private
---Awaits the task.
---@return any
function Task:await()
  local co = coroutine.running()
  if not co or coroutine.status(co) == "dead" then
    error("Need active async context")
  end
  if self.m_status == 0 then
    self.m_cb = function(...)
      self.m_result = table_pack(...)
      assert(coroutine.resume(co))
    end
    if self:start() then
      if self.m_status == -1 then
        coroutine.yield()
      end
      return table_unpack(self.m_result)
    end
  end
end

--Creates a task that will complete after a time delay (ms).
---@param delay number Delay in milliseconds.
---@return lviz.async.Task
function Task.Delay(delay)
  return Task.new(defer_fn, 0, delay)
end

return Task
