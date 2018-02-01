use constant EIT_FILE_NAME => "eit.pat";

open( my $eit_file, ">", EIT_FILE_NAME)
    or die "Can't open file", EIT_FILE_NAME;
    

# EIT function with 251 data bytes
$eit_req = ":012B0D";
$sum = 0x1 + 0x2B + 0x0D;

for($i = 0; $i < 251; $i++){
    $eit_req .= sprintf("%02hhX", $i);
    $sum += $i
}

$eit_req .= "\n";

print $eit_file $eit_req;
print $eit_file ":012B0DC7\n"
