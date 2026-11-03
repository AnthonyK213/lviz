lviz.ui.log.Clear()
lviz.ui.view3d.Clear()

lviz.ui.view3d.Display(lviz.canvas.Label("The quick brown fox...", lviz.gp.Pnt(), 137));
lviz.ui.view3d.Display(lviz.canvas.Label("Jumps over the~", lviz.gp.Pnt(-10, 30, -20), 100));
lviz.ui.view3d.Display(lviz.canvas.Label("Lazy dog!", lviz.gp.Pnt(-30, -20, -10), 50));
lviz.ui.view3d.Display(lviz.canvas.Label("Lazy 犬!", lviz.gp.Pnt(10, 20, 30), 50));
