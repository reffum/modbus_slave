# Generate ModBus test 
use constant WS_FILE_NAME => "write_single.pat";
use constant RH_FILE_NAME => "read_hold.pat";
use constant MAX_REG => 65536;
use constant MAX_RH => 125;
use constant ID => 1;

open(my $ws_file, ">", WS_FILE_NAME) 
    or die "Can't open file ", WS_FILE_NAME;

open( my $rh_file, ">", RH_FILE_NAME) 
    or die "Can't open file ", RH_FILE_NAME;

# Write single write all register with value = address
for($addr = 0; $addr < MAX_REG; $addr++)
{
    $value = $addr;
    $lrc =  lrc(1, 6, $addr >> 8, $addr & 0xFF, $value >> 8, $value & 0xFF);

    $req = ":0106"  
	. sprintf("%04hX", $addr)
	. sprintf("%04hX", $value)
	. sprintf("%02hhX", $lrc)
	."\n";

    #Responce(value = addr - 1)
    $value = $addr - 1;
    $lrc =  lrc(1, 6, $addr >> 8, $addr & 0xFF, $value >> 8, $value & 0xFF);

    $resp = ":0106"  
	. sprintf("%04hX", $addr)
	. sprintf("%04hX", $value)
	. sprintf("%02hhX", $lrc)
	."\n";    

    print $ws_file $req;
    print $ws_file $resp;
}

# Read hold.
# Read all register by 1, by 2 etc
for($addr = 0; $addr < MAX_REG; $addr++)
{
    # Registers vaues
    for($i = 0; $i < MAX_RH; $i++){
	$values[$i] = $addr + $i;
    }

    foreach $len (1,  min(MAX_RH, MAX_REG - $addr))
    {
	# Request
	$lrc = lrc(1, 3, $addr >> 8, $addr & 0xFF, $len >> 8, $len & 0xFF);
	$req = ":0103"
	    . sprintf("%04hX", $addr)
	    . sprintf("%04hX", $len)
	    . sprintf("%02hhX", $lrc)
	    . "\n";

	# Responce
	@regs = ();
	foreach $val (@values[0..$len - 1]){
	    push @regs, $val & 0xFF, ($val  >> 8)
	}
	$lrc = lrc(1, 3, $len * 2, @regs);

	$resp = ":0103"
	    . sprintf("%02hhX", $len * 2);
	
	foreach $val(@values[0..$len - 1]) {
	    $resp .=  sprintf("%04hX", $val);
	}
	
	$resp .= sprintf("%02hhX", $lrc)
	    . "\n";

	print $rh_file $req;
	print $rh_file $resp;
    }
}

close $ws_file;
close $rh_file;

# Return Modbus ASCII LRC for array
sub lrc
{
    $sum = 0;
    foreach $item(@_){
	$sum += $item;
    }

    $result = -($sum & 0xff);

    return $result;
}

#Return min of two integer
sub min
{
    $a0 = shift;
    $a1 = shift;

    return [$a0, $a1] -> [$a0 > $a1];
}
