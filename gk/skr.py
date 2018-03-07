print("create om 200 200")
for i in range(5):
	print("clip om {} {} {} {}".format(40*i, 0, 40*(i+1)-5, 200))
	print("fill om lrgb {} 1 {}".format(0.1*i, 1-0.1*i))
	print("clip om {} {} {} {}".format(40*(i+1)-5, 0, 40*(i+1), 200))
	print("fill om lrgb {} 0 {}".format(0, 0))
print("save lrgb.png om")

print("create om1 200 200")
for i in range(5):
	print("clip om1 {} {} {} {}".format(40*i, 0, 40*(i+1)-5, 200))
	print("fill om1 srgb {} 1 {}".format(0.1*i, 1-0.1*i))
	print("clip om1 {} {} {} {}".format(40*(i+1)-5, 0, 40*(i+1), 200))
	print("fill om1 srgb {} 0 {}".format(0, 0))
print("save srgb.png om1")

print("create om2 200 200")
for i in range(5):
	print("clip om2 {} {} {} {}".format(40*i, 0, 40*(i+1)-5, 200))
	print("fill om2 xyz {} 1 {}".format(0.1*i, 1-0.1*i))
	print("clip om2 {} {} {} {}".format(40*(i+1)-5, 0, 40*(i+1), 200))
	print("fill om2 xyz {} 0 {}".format(0, 0))
print("save xyz.png om2")
print("exit 0")
