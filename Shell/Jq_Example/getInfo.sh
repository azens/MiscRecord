jq '.data.video' videoinfo.json
jq '.data|length' videoinfo.json
jq '.data|keys' videoinfo.json
jq '{img:.data.img,video:.data.video}' videoinfo.json
jq '.data|{img:.img,video:.video}' videoinfo.json
jq '.data|[.img,.video]' videoinfo.json
jq '.data|.img,.video' videoinfo.json
jq '.data|keys[0,2]' videoinfo.json
