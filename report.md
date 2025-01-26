# 数式の計算機の改良に関するレポート

## 1. 小数点以下の数値解釈の実装

### a) 正規表現とDFA

#### 正規表現
小数点以下の数値を解釈する正規表現：
```
([1-9][0-9]*|0)(\.[0-9]+)?
```


![alt text](images/image.png)
<div style="page-break-before:always"></div>

## 2. 単独マイナス使用の実装

### a) 修正したCFG G''
```
G''
S → <項> { (+ | -) <項> }
<項> → <因子> { (* | /) <因子> }
<因子> → - <基本式> | <基本式>
<基本式> → ( S ) | x
```

### プログラムの実行例

#### 正常な実行
```
> 12.34
        12.340000
> -(1+2)
        -3.000000
> 4+(-5*5)
        -21.000000
```

#### 不正な実行
```
> 01.23
        invalid character!
        invalid expression!
> .45
        invalid character!
        invalid expression!
> 12.
        invalid character!
        invalid expression!
```

#### 演算子の重複
```
> 3+-4
        Multiple operators not allowed
        invalid expression!
> 3++4
        Multiple operators not allowed
        invalid expression!
```