import sys
sccname = sys.argv[1]
snapname = sys.argv[2]
sccf = open(sccname, "r+")
lines = sccf.readlines()
scc = []
for l in lines:
	l = l.rstrip().split("\t")
	ac = set()
	for ele in l:
		ac.add(int(ele))
	scc.append(sorted(ac))
sccf.close()
sorted(scc,key=len)

snapf = open(snapname, "r+")
lines = snapf.readlines()
snap = []
cnt = 0
for l in lines:
	if cnt < 3:
		cnt += 1
		continue
	l = l.rstrip().split("\t")
	ac = set()
	for ele in l[1:]:
		ac.add(int(ele))
	snap.append(sorted(ac))
snapf.close()
sorted(snap,key=len)
flag = 1
cnt=0
for item in scc:
	for ref in snap:
		if item == ref:
			cnt += 1
			flag = 0
			break
	if flag == 0:
		snap.remove(item)
		print("checked:{} remain:{}".format(cnt,len(snap)))
		flag = 1
	else:
		print("not exist:{}".format(item))
		break
print("identical same")

