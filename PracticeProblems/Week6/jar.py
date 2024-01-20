class Jar:
    def __init__(self, capacity=12):
        if (isinstance(capacity, int) and capacity > 0):
            self._capacity = capacity
            self._size = 0
        else:
            raise ValueError("Capacity must be a POSITIVE INTEGER!")

    def __str__(self):
        return "🍪" * self._size

    def deposit(self, n):
        if (self._size + n) < self.capacity:
            self._size += n
        else:
            raise ValueError(f"Adding {n} cookies would exceed jars capacity!")

    def withdraw(self, n):
        if (self._size - n) >= 0:
            self._size -= n
        else:
            raise ValueError(f"Not enough cookies in the jar!")

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

def main():
    jar = Jar()
    print(str(jar.capacity))
    print(str(jar))
    jar.deposit(2)
    print(str(jar))
    jar.withdraw(1)
    print(str(jar))

main()
