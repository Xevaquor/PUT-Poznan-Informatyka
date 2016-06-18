import os

victims = """lab-os-1
lab-os-2
lab-os-3
lab-os-4
lab-os-5
lab-os-6
lab-os-7
lab-os-8
lab-os-9
lab-os-10
lab-os-11
lab-os-12
lab-os-13
lab-os-14
lab-os-15
lab-os-16
lab-sec-1
lab-sec-2
lab-sec-3
lab-sec-4
lab-sec-5
lab-sec-6
lab-sec-7
lab-sec-8
lab-sec-9
lab-sec-10
lab-sec-11
lab-sec-12
lab-sec-13
lab-sec-14
lab-sec-15
lab-sec-16
lab-net-1
lab-net-2
lab-net-3
lab-net-4
lab-net-5
lab-net-6
lab-net-7
lab-net-8
lab-net-9
lab-net-10
lab-net-11
lab-net-12
lab-net-13
lab-net-14
lab-net-15
lab-net-16"""

for v in victims.split():
    alive = os.system("ping -c 1 -w 1 {} > /dev/null 2>&1".format(v))
    if alive == 0:
        print(v)
