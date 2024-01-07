import pytest
from utils import BigNumber
from itertools import zip_longest

def test_fun():
    BigNumber.fun(1) == 1 

class Test_BigNumber:
    @staticmethod
    @pytest.mark.xfail(raises=ValueError)
    def test_value_of():
        BigNumber.BigNumber.value_of(None,None)