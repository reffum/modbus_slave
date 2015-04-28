
$addr = 0x0080;
$value = $addr;

print sprintf("%02hhX", lrc(1, 6, $addr >> 8, $addr & 0xFF, $value >> 8, $value & 0xff));

# Return Modbus ASCII LRC for array
sub lrc
{
    $sum = 0;
    foreach $item(@_){
	print $item . "\n";
	$sum += $item;
    }
    $result = -($sum & 0xff);

    return $result;
}
