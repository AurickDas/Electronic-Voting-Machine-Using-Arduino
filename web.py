import webbrowser
import pandas as pd
import math
sheet_url =f"https://docs.google.com/spreadsheets/d/14iX0m77UNxlGCr5aG9uRALwEWk7TvrM-C68N3k1d864/edit#gid=0"

url_1 = sheet_url.replace('/edit#gid=', '/export?format=csv&gid=')

# Read the csv file in
df = pd.read_csv(url_1)

# # first row read
# # print(df)
# # display(df)
# # print("len "+str(len(df)))
# for i in range(len(df)):
#     j=0
#     for col in df.columns:
#         # print("col")
#         # print(col)
#         j=j+1
#         if j==1 or j==2:
#             continue
#         value = math.floor(float(col))
#         print(str(value)+"\n")

# count total votes and decide winner
maxvote=-1
maxidx=-1
votecount=0
for i in range(len(df)):
    j=0
    for col in df.columns:
        j=j+1
        if j==1 or j==2:
            continue
        value = int(df.iloc[i][col])
        votecount=votecount+value
        if value>maxvote:
            maxvote=value
            maxidx=j-2

drawflag=0
for i in range(len(df)):
    j=0
    for col in df.columns:
        j=j+1
        if j==1 or j==2 or j==maxidx+2:
            continue
        value = int(df.iloc[i][col])
        if value==maxvote:
            drawflag=1
            break

winnername=""
if maxidx==1:
    winnername="candidate1"
elif maxidx==2:
    winnername="candidate2"
else:
    winnername="candidate3"

drawprompt="The election resulted in a DRAW !!"

# convert votecount to string
votecountstr=""
if votecount<10:
    votecountstr="0"+str(votecount)
else:
    votecountstr=str(votecount)

with open(r'p.html', 'w+') as f:
    f.write("<!DOCTYPE html>\n")
    f.write("<html>\n")
    f.write('<head>\n')
    f.write('\t<link rel="stylesheet" href="homepage (2).css">\n')
    f.write('</head>\n')
    f.write('<body>\n')
    f.write('<div class="maindiv">')
    f.write('\t<h1 class="heading">Welcome to Our EVM Machine</h1>\n')
    f.write('\t<h2 id="displayDateTime" class="datetime"></h2>\n')
    f.write('\t<h2 class="voteinfo1">Total Candidates: 03</h2>\n')
    f.write('\t<h2 class="voteinfo2">Total Registered Voters: 03</h2>\n')
    f.write('\t<h2 class="voteinfo3">Total Votes Cast: '+votecountstr+'</h2>\n')

    f.write('\t<div class="tablediv">\n')
    f.write('\t\t<table class="styled-table">\n')
    f.write('\t\t\t<thead>\n')
    f.write('\t\t\t\t<tr>\n')
    f.write('\t\t\t\t\t<th>Candidate 1</th>\n')
    f.write('\t\t\t\t\t<th>Candidate 2</th>\n')
    f.write('\t\t\t\t\t<th>Candidate 3</th>\n')
    f.write('\t\t\t\t</tr>\n')
    f.write('\t\t\t</thead>\n')

    f.write('\t\t\t<tbody>\n')
    f.write('\t\t\t\t<tr>\n')
    # f.write('\t\t\t\t\t<td>0</td>\n')
    # f.write('\t\t\t\t\t<td>0</td>\n')
    # f.write('\t\t\t\t\t<td>0</td>\n')
    for i in range(len(df)):
        j=0
        for col in df.columns:
            j=j+1
            if j==1 or j==2:
                continue
            value = df.iloc[i][col]
            f.write('\t\t\t\t\t<td>'+str(value)+'</td>\n')
    f.write('\t\t\t\t</tr>\n')
    f.write('\t\t\t</tbody>\n')
    f.write('\t\t</table>\n')
    f.write('\t</div>\n')

    f.write('\t<div class="winner">\n')
    if drawflag==0:
        f.write('\t\t<h1 class="winnerline">The winner is '+winnername+' !!</h1>\n')
    else:
        f.write('\t\t<h1 class="winnerline">'+drawprompt+'</h1>\n')
    f.write('\t<div class="winner">\n')
    f.write('</div>\n')
    # f.write('<table>')
    # for header in df.columns.values:
    #     f.write('<th>'+str(header)+'</th>')
    # for i in range(len(df)):
    #     f.write('<tr>')
    #     for col in df.columns:
    #         value = df.iloc[i][col]
    #         f.write('<td>'+str(value)+'</td>')
    #     f.write('</tr>')
    # f.write('</table>')
    f.write('</body>\n')
    f.write('<script type="text/javascript">\n')
    f.write('\tvar today = new Date();\n')
    f.write('\tvar day = today.getDay();\n')
    f.write('\tvar date = today.getFullYear()+"-"+(today.getMonth()+1)+"-"+today.getDate();\n')
    f.write('\tvar time = today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();\n')
    f.write('\tvar dateTime = date+" "+time;\n')
    f.write('\tdocument.getElementById("displayDateTime").innerHTML = dateTime;\n')
    f.write('</script>\n')
    f.write('</html>\n')
webbrowser.open_new_tab('p.html')


