echo '{ "data": "PlayerID, Level, Score, Units, Gold, Potions, Friends, InventoryItems" }'
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "32036, 25, 87821, 391, 4456, 733, 334, 456" } => Fraud'
# /usr/bin/time -p curl -d '{ "data": "32036, 25, 87821, 391, 4456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "32036, 25, 87821, 391, 4456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "1132036, 25, 87821, 391, 4456, 733, 334, 456" } => ??'
# /usr/bin/time -p curl -d '{ "data": "1132036, 25, 87821, 391, 4456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "1132036, 25, 87821, 391, 4456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "32036, 250, 87821, 391, 4456, 733, 334, 456" } => Level => ??'
# /usr/bin/time -p curl -d '{ "data": "32036, 250, 87821, 391, 4456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "32036, 250, 87821, 391, 4456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "32036, 25, 8782, 391, 4456, 733, 334, 456" } => Score => ??'
# /usr/bin/time -p curl -d '{ "data": "32036, 25, 8782, 391, 4456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "32036, 25, 8782, 391, 4456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "32036, 25, 87821, 1391, 4456, 733, 334, 456" } => Units => ??'
# /usr/bin/time -p curl -d '{ "data": "32036, 25, 87821, 1391, 4456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "32036, 25, 87821, 1391, 4456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "32036, 25, 87821, 391, 14456, 733, 334, 456" } => Gold => ??'
# /usr/bin/time -p curl -d '{ "data": "32036, 25, 87821, 391, 14456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "32036, 25, 87821, 391, 14456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "32036, 25, 87821, 391, 456, 733, 334, 456" } => Gold => ??'
# /usr/bin/time -p curl -d '{ "data": "32036, 25, 87821, 391, 456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "32036, 25, 87821, 391, 456, 733, 334, 456" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "32036, 25, 27821, 191, 156, 133, 134, 56" } => TRANSFORMED?'
# /usr/bin/time -p curl -d '{ "data": "32036, 25, 27821, 191, 156, 133, 134, 56" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "32036, 25, 27821, 191, 156, 133, 134, 56" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "28583, 33, 185402, 499, 6905, 937, 464, 588" } => Fraud'
# /usr/bin/time -p curl -d '{ "data": "28583, 33, 185402, 499, 6905, 937, 464, 588" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "28583, 33, 185402, 499, 6905, 937, 464, 588" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "37474, 31, 33373, 176, 138, 125, 506, 146" } => Valid'
# /usr/bin/time -p curl -d '{ "data": "37474, 31, 33373, 176, 138, 125, 506, 146" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "37474, 31, 33373, 176, 138, 125, 506, 146" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "49092, 21, 18083, 115, 105, 92, 253, 94" } => Valid'
# /usr/bin/time -p curl -d '{ "data": "49092, 21, 18083, 115, 105, 92, 253, 94" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "49092, 21, 18083, 115, 105, 92, 253, 94" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "23499, 23, 24679, 124, 120, 97, 305, 110" } => Valid'
# /usr/bin/time -p curl -d '{ "data": "23499, 23, 24679, 124, 120, 97, 305, 110" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "23499, 23, 24679, 124, 120, 97, 305, 110" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "12612, 15, 9465, 90, 68, 76, 179, 66" } => Valid'
# /usr/bin/time -p curl -d '{ "data": "12612, 15, 9465, 90, 68, 76, 179, 66" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "12612, 15, 9465, 90, 68, 76, 179, 66" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "12612, 15, 9465, 90, 168, 76, 179, 66" } => ??'
# /usr/bin/time -p curl -d '{ "data": "12612, 15, 9465, 90, 168, 76, 179, 66" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "12612, 15, 9465, 90, 168, 76, 179, 66" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "12612, 15, 9465, 90, 208, 206, 179, 66" } => ??'
# /usr/bin/time -p curl -d '{ "data": "12612, 15, 19465, 90, 208, 206, 179, 66" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "12612, 15, 9465, 90, 208, 206, 179, 66" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "12612, 25, 9465, 90, 208, 206, 179, 66" } => ??'
# /usr/bin/time -p curl -d '{ "data": "12612, 25, 19465, 90, 208, 206, 179, 66" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "12612, 25, 9465, 90, 208, 206, 179, 66" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "12612, 40, 19465, 190, 208, 206, 79, 66" } => ??'
# /usr/bin/time -p curl -d '{ "data": "12612, 40, 19465, 190, 208, 206, 79, 66" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "12612, 40, 19465, 190, 208, 206, 79, 66" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
# read -rsp $'' -n1 key
echo '{ "data": "12612, 15, 9465, 90, 268, 176, 179, 66" } => ??'
# /usr/bin/time -p curl -d '{ "data": "12612, 15, 9465, 90, 268, 176, 179, 66" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
curl -d '{ "data": "12612, 15, 9465, 90, 268, 176, 179, 66" }' -X POST https://g7vg73nrg6.execute-api.ap-southeast-2.amazonaws.com/Demo/isvalidrpgamedata -w "\n"
echo '----------------------------------------------'
