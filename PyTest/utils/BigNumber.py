from itertools import zip_longest
def fun(a:int):
    return a

# BigNumber is a class that represents a number with a large number of digits.
class BigNumber:
    # Basic constructor that takes two bytearrays, one for the integrer part and one for the fractional part.
    def __init__(self, integrer: bytearray, frac: bytearray):
        if integrer is None or frac is None:
            raise ValueError("Integrer and frac must not be None")
        if len(integrer) < 1 or len(frac) == 0:
            raise ValueError("Integrer must not be empty")
        if len(integrer) > 1 and integrer[0] == "0":
            raise ValueError("Integrer must not have leading zeros")
        if not integrer.isdigit() or not frac.isdigit():
            raise ValueError("Integrer and frac must be digits")
        
        self.__integrer = integrer.copy()
        self.__frac = frac.copy()


    # Returns a string representation of the number.
    def __str__(self):
        return f"{self.__integrer.decode()}.{self.__frac.decode()}"
    

    # Static method that returns a BigNumber object from a bytearrays, one for the integrer part and one for the fractional part.
    @staticmethod
    def value_of(integrer: bytearray, frac: bytearray):
        if integrer is None or frac is None:
            raise ValueError("Integrer and frac must not be None")
        if len(integrer) > 1 and integrer[0] == "0":
            raise ValueError("Integrer must not have leading zeros")
        if len(frac) == 1 and frac[0] == "0":
            if len(integrer) == 1:
                if integrer[0] == "0":
                    return BigNumber.ZERO
                elif integrer[0] == "1":
                    return BigNumber.ONE
                elif integrer[0] == "2":
                    return BigNumber.TWO
            elif len(integrer) == 2 and integrer[0] == "1" and integrer[1] == "0":
                return BigNumber.TEN
        return BigNumber(integrer, frac)


    # Getter methods.
    def get_integrer(self):
        return self.__integrer.copy()
    

    def get_frac(self):
        return self.__frac.copy()

    
    # Returns the absolute value of the number.
    def floor(self):
        return BigNumber(self.__integrer.copy(), BigNumber.ONE.get_integrer())
    

    # Equality method
    def __eq__(self, __value: object):
        if isinstance(__value, BigNumber):
            return self.__integrer == __value.__integrer and self.__frac == __value.__frac
        return False
    

    # Inequality method
    def __ne__(self, __value: object):
        return not self.__eq__(__value)
    

    # Less than method
    def __lt__(self, __value: object):
        if isinstance(__value, BigNumber):
            if self.__integrer == __value.__integrer:
                return self.__frac > __value.__frac
            return self.__integrer < __value.__integrer
        return False
    

    # Less than or equal method
    def __le__(self, __value: object):
        return self.__lt__(__value) or self.__eq__(__value)
    

    # Greater than method
    def __gt__(self, __value: object):
        if isinstance(__value, BigNumber):
            if self.__integrer == __value.__integrer:
                return self.__frac > __value.__frac
            return self.__integrer > __value.__integrer
        return False
    

    # Greater than or equal method
    def __ge__(self, __value: object):
        return self.__gt__(__value) or self.__eq__(__value)
    

    # Addition method
    def __add__(self, __value: object):
        if isinstance(__value, BigNumber):
            integrer = bytearray()
            frac = bytearray()
            carry = 0
            for a, b in zip_longest(reversed(self.__frac.decode()), reversed(__value.__frac.decode()), fillvalue="0"):
                c = int(a) + int(b) + carry
                carry = c // 10
                frac.append(c % 10)
            for a, b in zip_longest(reversed(self.__integrer.decode()), reversed(__value.__integrer.decode()), fillvalue="0"):
                c = int(a) + int(b) - carry
                carry = c // 10
                integrer.append(c % 10)
            if carry > 0:
                integrer.append(carry)
            integrer.reverse()
            frac.reverse()
            integrer = bytearray(map(lambda x: ord(x) + 48, integrer.decode()))
            frac = bytearray(map(lambda x: ord(x) + 48, frac.decode()))
            return BigNumber(integrer, frac)
        raise ValueError("Value must be BigNumber")
    

    # Subtraction method (under development)
    def __sub__(self, __value: object):
        pass


# Static variables that represent the most common numbers.
BigNumber.ZERO = BigNumber(bytearray(b"0"), bytearray(b"0"))
BigNumber.ONE = BigNumber(bytearray(b"1"), bytearray(b"0"))
BigNumber.TWO = BigNumber(bytearray(b"2"), bytearray(b"0"))
BigNumber.TEN = BigNumber(bytearray(b"10"), bytearray(b"0"))
