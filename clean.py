import sys
name = sys.argv[1]
newname = sys.argv[2]
f = open(name, "r+")
o = open(newname, "w")
l = f.readline()
l = l.rstrip().split(" ")
n = l[0]
m = l[1]
cnt = 0
order = dict()
o.write("{}\t{}\n".format(n,m))
for i in range(int(m)):
	l = f.readline()
	l = l.rstrip()
	l = l.split("\t")
	print(l)
	s = l[0]
	d = l[1]
	if s not in order:
		order[s] = cnt
		cnt += 1
	if d not in order:
		order[d] = cnt
		cnt += 1
	o.write("{}\t{}\n".format(order[s],order[d]))
f.close()
o.close()
