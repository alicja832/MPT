iimport pytest
from utils import BigNumber
from itertools import zip_longest

bytearray_1=bytearray(b"10")
bytearray_2= bytearray(b"00")
bytearray_3= bytearray(b"11")
bytearray_4= bytearray(b"1")
bytearray_5= bytearray(b"0")


def test_fun():
    BigNumber.fun(1) == 1 

class Test_BigNumber:
    @staticmethod
    def test_value_of():
        with pytest.raises(ValueError,match="Integrer and frac must not be None"):
            BigNumber.BigNumber.value_of(None,None)
    # tego nie wiem jak zrobic
    # @staticmethod
    # def test_value_of():
    #     with pytest.raises(ValueError,match="Integrer must not have leading zeros"):
    #         BigNumber.BigNumber.value_of(bytearray_2,bytearray_2)
    
    #constructors
    def test_BigNumber(self):
        with pytest.raises(ValueError):
            BigNumber.BigNumber(None,None)
    def test_BigNumber(self):
        with pytest.raises(ValueError,match="Integrer and frac must be digits"):
            BigNumber.BigNumber('a','a')
    def test__str__(self):
        a=BigNumber.BigNumber(bytearray_1, bytearray_2)
        assert a.__str__() == f"{bytearray_1.decode()}.{bytearray_2.decode()}"
    def test_get_integrer(self):
        a=BigNumber.BigNumber(bytearray_1, bytearray_2)
        assert a.get_integrer() == bytearray_1
    def test_get_frac(self):
        a=BigNumber.BigNumber(bytearray_1, bytearray_2)
        assert a.get_frac() == bytearray_2
    def test_floor(self):
        a=BigNumber.BigNumber(bytearray_1, bytearray_2)
        b=BigNumber.BigNumber(bytearray_1, bytearray_4)
        assert a.floor() == b 
    def test__eq__(self):
        a=BigNumber.BigNumber(bytearray_1, bytearray_2)
        b=BigNumber.BigNumber(bytearray_1, bytearray_2)
        assert ( a == b ) == True
    def test__ne__(self):
        a=BigNumber.BigNumber(bytearray_1, bytearray_2)
        b=BigNumber.BigNumber(bytearray_2, bytearray_3)
        assert ( a != b ) == True
    def test__lt__(self):
        a=BigNumber.BigNumber(bytearray_1, bytearray_2)
        b=BigNumber.BigNumber(bytearray_2, bytearray_2)
        assert (b < a) == True 
    def test__le__(self):
        a=BigNumber.BigNumber(bytearray_1, bytearray_2)
        b=BigNumber.BigNumber(bytearray_2, bytearray_2)
        assert (b <= a) == True
    def test__gt__(self):
        a=BigNumber.BigNumber(bytearray_1, bytearray_2)
        b=BigNumber.BigNumber(bytearray_2, bytearray_2)
        assert (a > b) == True 
    def test__ge__(self):
        a=BigNumber.BigNumber(bytearray_1, bytearray_2)
        b=BigNumber.BigNumber(bytearray_2, bytearray_2)
        assert (a >= b) == True 
    def test__add__(self):
        a=BigNumber.BigNumber(bytearray_1, bytearray_2)
        with pytest.raises(ValueError,match="Value must be BigNumber"):
            a + 2 
    def test__add__(self):
        a=BigNumber.BigNumber(bytearray_1, bytearray_2)
        with pytest.raises(ValueError,match="Value must be BigNumber"):
            a + 2  
    
