<?php
header('Access-Control-Allow-Origin: *');
require 'config.php';
extract($_GET);
define('DIR_SAVE_TEST', $CONFIG['DIR_SAVE_TEST']);
define('DIR_SAMPLE', 'sample');
define('PATH', $CONFIG['PATH']);
define('SP', dirname(__FILE__));
define('rw', $CONFIG['REWRITE_IF_EXITS']);
function _run($command)
{
    return shell_exec($command);
};
function filter($string)
{
    return str_replace('&nbsp;', '', $string);
};
function _writeFile($text, $ext, $id)
{
    $name = $id . $ext;
    $fopen = fopen(constant('DIR_SAVE_TEST') . '\\' . $GLOBALS['probName'] . '\\' . constant('DIR_SAVE_TEST') . '\\' . $name, 'w') or die('Cant open file');
    fwrite($fopen, $text);
    fclose($fopen);
};
function _return($succ, $msg)
{
    echo $msg;
};
if (isset($info))
{
    $info = json_decode($info);
    $probName = $info->name;
    $testCase = $info->testcase;
    if (!is_dir(constant('DIR_SAVE_TEST'))) mkdir(constant('DIR_SAVE_TEST'));
    if (!is_dir(constant('DIR_SAVE_TEST') . '\\' . $probName))
    {
        mkdir(constant('DIR_SAVE_TEST') . '\\' . $probName);
        mkdir(constant('DIR_SAVE_TEST') . '\\' . $probName . '\\' . constant('DIR_SAVE_TEST'));
        $GLOBALS['probName'] = $probName;
        for ($i = 0;$i < count($testCase);$i++)
        {
            $input = filter($testCase[$i]->input);
            $output = filter($testCase[$i]->output);
            _writeFile($input, '.inp', $i);
            _writeFile($output, '.out', $i);
        };
        $move = 'xcopy "' . constant('SP') . '\\' . constant('DIR_SAVE_TEST') . '" "' . constant('PATH') . '" /E /H /R /X /I /K';
        $del = 'RD /S /Q "' . constant('SP') . '\\' . constant('DIR_SAVE_TEST') . '\\' . $GLOBALS['probName'] . '"';
        _run($move);
        _run($del);
        $moveSample = 'xcopy "' . constant('SP') . '\\' . constant('DIR_SAMPLE') . '" "' . constant('PATH') . '\\' . $GLOBALS['probName'] . '" /E /H /R /X /I /K';
        _run($moveSample);
        $runCPP = '"' . constant('PATH') . '\\' . $GLOBALS['probName'] . '\\solution.cpp"';
        _run($runCPP);
    }
    else
    {
        _return(false, 'Da ton tai bai tap nay!');
    };
};
?>
