// Java大整数
import java.util.*;
import java.math.*;

public class BigInt {
    static Scanner in = new Scanner(System.in); // 定义输入对象
    public static void main(String[] args) {
        BigInteger bigInt_1 = new BigInteger("100");
        BigInteger bigInt_2 = BigInteger.valueOf(123);
        //两种定义方式，建议使用第一种
        bigInt_1.add(bigInt_2); // 加法
        bigInt_1.subtract(bigInt_2); // 减法
        bigInt_1.multiply(bigInt_2); // 乘法
        bigInt_1.divide(bigInt_2);// 除法，向下取整
        bigInt_1.divideAndRemainder(bigInt_2);
            // 返回一个BigInteger[]，包含商和余数
        bigInt_1.remainder(bigInt_2); // 取余数，与this同符号
        bigInt_1.mod(bigInt_2); // 取模，模数只能为正整数
        bigInt_1.pow(10); // a^b
        bigInt_1.gcd(bigInt_2); // 最大公约数
        bigInt_1.compareTo(bigInt_2);
            // 比较大小，<0表示this小，0表示相等，>0表示this大
        bigInt_1.equals(bigInt_2); // 真值为相等
        bigInt_1.negate(); // -a
        bigInt_1.abs(); // 绝对值
        bigInt_1.min(bigInt_2); // 最小值
        bigInt_1.max(bigInt_2); // 最大值
        BigInteger a = in.nextBigInteger(); // 读入
        System.out.println(bigInt_1); // 输出
    }
}

// Java大实数
import java.util.*;
import java.math.*;

public class Big {
    static Scanner in = new Scanner(System.in); // 定义输入对象
    public static void main(String[] args) {
        BigDecimal bigDec_1 = new BigDecimal("123.1");
        BigDecimal bigDec_2 = BigDecimal.valueOf(233.213);
        // 唯有除法与BigInteger不同，无限小数需要规定保留位数
        int scale = 3; // 保留位数
        bigDec_1.divide(bigDec_2, scale, RoundingMode.HALF_UP);
        /*
            第三个参数为保留方式，有以下几种：
            CEILING 正无穷大方向取整
            FLOOR 负无穷大方向取整
            DOWN 向 0 的方向取整
            UP	正数向正无穷大取整，负数向负无穷大取整
            HALF_UP 常用的4舍5入
            HALF_DOWN 6,7,8,9 向上取整
            HALF_EVEN 小数位是5时，判断整数部分是奇数就进位，6,7,8,9 进位
         */
    }
}