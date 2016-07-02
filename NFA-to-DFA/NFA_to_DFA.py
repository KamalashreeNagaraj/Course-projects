#generates powerset of given set
def powerset(seq):
    if len(seq) <= 1:
        yield seq
        yield []
    else:
        for item in powerset(seq[1:]):
            yield [seq[0]]+item
            yield item

def generate_dfa(ss , tt) :
    for k in range(0,len(tt)) :
        if ss == tt[k][0]:
            if tt[k][-1] == 1:
                return tt
            tt[k].append(1)
            for j in range(1,len(dfa[k])) :
                tt = generate_dfa(tt[k][j],tt)
    return tt
a = [] 
maxLengthList = int(raw_input("Enter the number of states : "))
print "Enter the states : "
#Append the states to an array
while len(a) < maxLengthList:
    item = raw_input()
    a.append(item)
#call powerset function for the input array of states 
r = [x for x in powerset(a)] #powerset of states
c = []
d = []
f=int(raw_input("Enter the number of symbols : "))
print "Enter the symbols : "
#Append the symbols to an array
for i in range (0,f) :
    item=raw_input()
    d.append(item)
#Dimension of the input table
#Enter a symbol per line row-wise
maxlength = len(a)*(f+1)
print "Enter the table : "
while len(c) < maxlength:
    it=list(raw_input().split())
    c.append(it)
start = [raw_input("Enter the start state : ")]
dfa = [[]]
#Generates transition table
for i in range(0,2**len(a)):
    #print r[i],
    if i == 0 : dfa[i].append(list(r[i]))
    else : dfa.append([r[i]])
    for m in range(0,len(d)):
        temp = []
        #print "         ",
        for j in range(0,len(r[i])):
            for k in range (0,len(c),(f+1)):
                if [r[i][j]] == c[k]:
                    for n in c[k+m+1] :
                        #print n,
                        temp.append(n)
        #removes repeated state outcomes
        temp1 = list(set(temp))
        temp1.sort()
        dfa[i].append(temp1)
    #print " "
    #print " "
dfa = generate_dfa(start,dfa)
print "Deterministic Finite Automaton for the above given NFA "
for i in range(0,f):
    print "         ",d[i],
print " "
for i in range(0,len(dfa)):
    if dfa[i][-1] == 1 :
        for x in dfa[i][:3]:
            print x,"   ",
        print " "
