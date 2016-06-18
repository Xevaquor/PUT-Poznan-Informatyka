# The authors of this work have released all rights to it and placed it
# in the public domain under the Creative Commons CC0 1.0 waiver
# (http://creativecommons.org/publicdomain/zero/1.0/).
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
# 
# Retrieved from: http://en.literateprograms.org/Quicksort_(Python)?oldid=19197

def qsort1(list):
    """Quicksort using list comprehensions"""
    if list == []: 
        return []
    else:
        pivot = list[0]
        lesser = qsort1([x for x in list[1:] if x < pivot])
        greater = qsort1([x for x in list[1:] if x >= pivot])
        return lesser + [pivot] + greater

def partition(list, l, e, g):
    while list != []:
        head = list.pop(0)
        if head < e[0]:
            l = [head] + l
        elif head > e[0]:
            g = [head] + g
        else:
            e = [head] + e
    return (l, e, g)
def qsort2(list):
    """Quicksort using a partitioning function"""
    if list == []: 
        return []
    else:
        pivot = list[0]
        lesser, equal, greater = partition(list[1:], [], [pivot], [])
        return qsort2(lesser) + equal + qsort2(greater)
def testQSort(qsort, stimulus, response, test):
    result = qsort(stimulus)
    if response == result:
        print qsort.__name__ + " - passed - " + test
    else:
        print qsort.__name__ + " - failed - " + test
        print "Expected: ",
        print response
        print "Got: ",
        print result
def testNumericSort(f):
    stimulus = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3]
    response = [1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 8, 9, 9, 9]
    testQSort(f, stimulus, response, "numeric sort")
    
def testStringSort(f):       
    stimulus = ["bob","alice","barry","zoe","charlotte","fred","marvin"]
    response = ["alice","barry","bob","charlotte","fred","marvin","zoe"]
    testQSort(f, stimulus, response, "string sort")

if __name__ == "__main__":
    print "Testing quicksort implementations..."
    qsorts = [qsort1, qsort2]
    for q in qsorts:
        testNumericSort(q)
        testStringSort(q)