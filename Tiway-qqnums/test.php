<?php
class QQNumbers {

    //创建12个为一个批次列表
    protected $listCount = 12;

    public function gNumCheck($str)
    {
        //5个及以上重复的数字
        $pattern='/([\d])\1{4,}/';
        preg_match($pattern,$str,$arr);
        if ($arr[0]??false){
            return false;
        }
        //两组及以上四个相同数字
        $pattern='/([\d])\1{3,}([\d])\2{3,}/';
        preg_match($pattern,$str,$arr);
        if ($arr[0]??false){
            return false;
        }
        //三组及以上三个相同数字
        $pattern='/([\d])\1{2,}([\d])\2{2,}([\d])\3{2,}/';
        preg_match($pattern,$str,$arr);
        if ($arr[0]??false){
            return false;
        }
        //三位连对
        $pattern='/(?:22(?=33)|33(?=44)|44(?=55)|55(?=66)|66(?=77)|77(?=88)|88(?=99)){3}\d/';
        preg_match($pattern,$str,$arr);
        if ($arr[0]??false){
            return false;
        }
        //两组以上AACC的对子
        $pattern='/(([\d]){1,}([\d]){1,})\1{1,}/';
        preg_match($pattern,$str,$arr);
        if ($arr[0]??false){
            return false;
        }
        //五位以上顺子
        $pattern='/(?:0(?=1)|1(?=2)|2(?=3)|3(?=4)|4(?=5)|5(?=6)|6(?=7)|7(?=8)|8(?=9)){4,}\d/';
        preg_match($pattern,$str,$arr);
        if ($arr[0]??false){
            return false;
        }
        //五位以上逆顺
        $pattern = '/(?:9(?=8)|8(?=7)|7(?=6)|6(?=5)|5(?=4)|4(?=3)|3(?=2)|2(?=1)|1(?=0)){4,}\d/';
        preg_match($pattern,$str,$arr);
        if ($arr[0]??false){
            return false;
        }
        //两组以上三位顺子ABCABC
        $pattern = '/((?:9(?=8)|8(?=7)|7(?=6)|6(?=5)|5(?=4)|4(?=3)|3(?=2)|2(?=1)|1(?=0)){2,}\d)\1/';
        preg_match($pattern,$str,$arr);
        if ($arr[0]??false){
            return false;
        }
        //两组以上三位逆顺子CBACBA
        $pattern = '/((?:0(?=1)|1(?=2)|2(?=3)|3(?=4)|4(?=5)|5(?=6)|6(?=7)|7(?=8)|8(?=9)){2,}\d)\1/';
        preg_match($pattern,$str,$arr);
        if ($arr[0]??false){
            return false;
        }
        //对称性
        $pattern = '/(\d)(\d)(\d)(\d)\4?\3\2\1/';
        preg_match($pattern,$str,$arr);
        if ($arr[0]??false){
            return false;
        }
        //爱情号
        $pattern = '/^5201314/';
        preg_match($pattern,$str,$arr);
        if ($arr[0]??false){
            return false;
        }

        return true;
    }

    //递归批量创建qq号
    public function creatBatchNumbers(array $gNumbers)
    {
        while (count($gNumbers) < $this->listCount) {
            $gNumber = mt_rand(10000000, 99999999);
            if ($this->gNumCheck($gNumber)) {
                $gNumbers[] = $gNumber;
            }
        }
        //TODO 去除已占用QQ号码
        //TODO 去除预占用列表
       
        return count($gNumbers) == $this->listCount ? $gNumbers : $this->creatGNumbers($gNumbers);
    }

    //获取可选的QQ号码
    public function getBatchQQNums()
    {
        //todo 限定获取次数
        //生成可用QQ号码列表
        $numArr = [];
        $numArr = $this->creatBatchNumbers($numArr);

        //TODO 失效该用户预占用qq号码
        //TODO记录可用QQ号码列表 作为该用户的预占用
    
        return ['qq_nums' => $numArr];
    }

}

$qqNums = (new QQNumbers())->getBatchQQNums();
var_dump($qqNums);



?>