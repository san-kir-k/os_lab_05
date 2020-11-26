import sys
import random
import string

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <test directory>")
        sys.exit(1)

    test_dir = sys.argv[1]

    line_count = [15, 5]
    for test_count in range(2):
        test = []

        # тест с невалидными данными
        if  test_count == 0:
            cmds = [0, 0, 1, 1, 1, 2, 2, 2]
            for _ in range(line_count[test_count]):
                idx = random.randint(0, 4)
                l = cmds[idx]
                val_list = [l]
                if l == 0:
                    val_list[0] = 0
                elif l == 1:
                    val_list.append(round(random.uniform(1.0, 10.0), random.randint(0, 5)))
                    val_list.append(round(random.uniform(1.0, 10.0), random.randint(0, 5)))
                else:
                    val_list.append(random.randint(-10000, 10005))
                test.append(val_list)
        
        # положительные и отрицательные числа без нуля
        if test_count == 1:
            test.append([3])
            test.append([1, -1.0, 109.09])
            test.append([2, "qwerty"])
            test.append(["Hello world"])
            test.append([42])

        test_name = "{}/tests_n_ans_t2/test_{}".format(test_dir, test_count + 1)
        with open(f'{test_name}.txt', 'w') as ftest:
            for t in test:
                isStart = 1
                for ts in t:
                    if isStart == 1:
                        isStart = 0
                    else:
                        ftest.write(f' ')
                    ftest.write(f'{ts}')
                ftest.write(f'\n')

main()
