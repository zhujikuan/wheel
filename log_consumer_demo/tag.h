#ifndef __NTA_TAG_H__
#define __NTA_TAG_H__

/* tag值说明：
 * https://confluence.qingteng.cn/pages/viewpage.action?pageId=98732661 */

extern char *device_ip;
extern char *device_id;
extern char *comid;

#define ADD_TLV_FORCE(catche, value, len, tag) \
    do {                                       \
        u16 T = tag;                           \
        vec_add(catche, &T, sizeof(u16));      \
        vec_add(catche, &len, sizeof(u16));    \
        if (len > 0) {                         \
            vec_add(catche, value, len);       \
        }                                      \
    } while (0);

#define ADD_TLV(catche, value, len, tag)        \
    do {                                        \
        if (len > 0) {                          \
            u16 T = tag;                        \
            vec_add(catche, &T, sizeof(u16));   \
            vec_add(catche, &len, sizeof(u16)); \
            vec_add(catche, value, len);        \
        }                                       \
    } while (0);

#define ADD_U32_TLV(catche, value, len, tag)    \
    do {                                        \
        if (len > 0) {                          \
            u16 T = tag;                        \
            vec_add(catche, &T, sizeof(u16));   \
            vec_add(catche, &len, sizeof(u32)); \
            vec_add(catche, value, len);        \
        }                                       \
    } while (0);

#define ADD_TLV_PUBLIC(catche, value, tag)    \
    do {                                      \
        u16 vlen = vec_len(value);            \
        if (vlen > 0) {                       \
            ADD_TLV(catche, value, vlen, tag) \
        }                                     \
    } while (0);

#define ADD_TV(catche, value, len, tag)       \
    do {                                      \
        if (len > 0) {                        \
            u16 T = tag;                      \
            vec_add(catche, &T, sizeof(u16)); \
            vec_add(catche, value, len);      \
        }                                     \
    } while (0);

#define ADD_LV(catche, value, len)          \
    do {                                    \
        vec_add(catche, &len, sizeof(u16)); \
        if (len > 0) {                      \
            vec_add(catche, value, len);    \
        }                                   \
    } while (0);

#define ADD_TL(catche, len, tag)            \
    do {                                    \
        u16 T = tag;                        \
        vec_add(catche, &T, sizeof(u16));   \
        vec_add(catche, &len, sizeof(u16)); \
    } while (0);

/* 公共字段 范围：0-999*/
/////////////////////////////////////////////////////////////////////////////////
/* 设备ID */
#define NTA_TAG_DEVICE_ID_1 1
#define ADD_DEVICE_ID(catche) \
    ADD_TLV_PUBLIC(catche, device_id, NTA_TAG_DEVICE_ID_1)

/* 公司ID */
#define NTA_TAG_COMPANY_ID_2 2
#define ADD_COMPANY_ID(catche) \
    ADD_TLV_PUBLIC(catche, comid, NTA_TAG_COMPANY_ID_2)

/* 源ipv4 */
#define NTA_TAG_SIP4_3 3
#define ADD_SIP4(catche, value) ADD_TV(catche, value, 4, NTA_TAG_SIP4_3)

/* 源ipv6 */
#define NTA_TAG_SIP6_4 4
#define ADD_SIP6(catche, value) ADD_TV(catche, value, 16, NTA_TAG_SIP6_4)

/* 目的ipv4 */
#define NTA_TAG_DIP4_5 5
#define ADD_DIP4(catche, value) ADD_TV(catche, value, 4, NTA_TAG_DIP4_5)

/* 目的ipv6 */
#define NTA_TAG_DIP6_6 6
#define ADD_DIP6(catche, value) ADD_TV(catche, value, 16, NTA_TAG_DIP6_6)

/* 源端口 */
#define NTA_TAG_SPORT_7 7
#define ADD_SPORT(catche, value) ADD_TV(catche, value, 2, NTA_TAG_SPORT_7)

/* 目的端口 */
#define NTA_TAG_DPORT_8 8
#define ADD_DPORT(catche, value) ADD_TV(catche, value, 2, NTA_TAG_DPORT_8)

/* 版本 */
#define NTA_TAG_VERSION_9 9
#define ADD_VERSION(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_VERSION_9)

/* L7状态 */
#define NTA_TAG_L7_STATUS_10 10
#define ADD_L7_STATUS(catche, value) \
    ADD_TV(catche, value, 2, NTA_TAG_L7_STATUS_10)

/* 业务开始时间 */
#define NTA_TAG_START_TIME_11 11
#define ADD_START_TIME(catche, value) \
    ADD_TV(catche, value, 8, NTA_TAG_START_TIME_11)

/* 业务结束时间  */
#define NTA_TAG_END_TIME_12 12
#define ADD_END_TIME(catche, value) \
    ADD_TV(catche, value, 8, NTA_TAG_END_TIME_12)

/* L4协议类型 */
#define NTA_TAG_L4_PROTOCOL_13 13
#define ADD_L4_PROTOCOL(catche, value) \
    ADD_TV(catche, value, 1, NTA_TAG_L4_PROTOCOL_13)

/* L7协议类型 */
#define NTA_TAG_L7_PROTOCOL_14 14
#define ADD_L7_PROTOCOL(catche, value) \
    ADD_TV(catche, value, 2, NTA_TAG_L7_PROTOCOL_14)

/* 账号 */
#define NTA_TAG_ACCOUNT_NAME_15 15
#define ADD_ACCOUNT_NAME(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_ACCOUNT_NAME_15)

/* 账号密码 */
#define NTA_TAG_ACCOUNT_PASSWORD_16 16
#define ADD_ACCOUNT_PASSWORD(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_ACCOUNT_PASSWORD_16)

/* 描述信息 */
#define NTA_TAG_DES_INFO_17 17
#define ADD_DES_INFO(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_DES_INFO_17)

/* 网卡名称 */
#define NTA_TAG_NETWORK_CARD_18 18
#define ADD_NETWORK_CARD(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_NETWORK_CARD_18)

/* 当前网卡接收到的总字节数 */
#define NTA_TAG_NET_RX_BYTES_19 19
#define ADD_NET_RX_BYTES(catche, value) \
    ADD_TV(catche, value, 8, NTA_TAG_NET_RX_BYTES_19)

/* 当前网卡接收到的总报文个数 */
#define NTA_TAG_NET_RX_PACKETS_20 20
#define ADD_NET_RX_PACKETS(catche, value) \
    ADD_TV(catche, value, 8, NTA_TAG_NET_RX_PACKETS_20)

/* 当前网卡接收数据的平均报文大小 */
#define NTA_TAG_NET_AVG_PKTS_LEN_21 21
#define ADD_NET_AVG_PKTS_LEN(catche, value) \
    ADD_TV(catche, value, 2, NTA_TAG_NET_AVG_PKTS_LEN_21)

/* 当前网卡的比特率，平均每秒收到多少bit位的数据 */
#define NTA_TAG_NET_BPS_22 22
#define ADD_NET_NET_BPS(catche, value) \
    ADD_TV(catche, value, 8, NTA_TAG_NET_BPS_22)

/* 当前网卡的网络吞吐率，平均每秒接收多少个数据包 */
#define NTA_TAG_NET_PPS_23 23
#define ADD_NET_NET_PPS(catche, value) \
    ADD_TV(catche, value, 8, NTA_TAG_NET_PPS_23)

/* 当前网卡一共丢了多少个报文 */
#define NTA_TAG_NET_RX_MISS_24 24
#define ADD_NET_NET_RX_MISS(catche, value) \
    ADD_TV(catche, value, 8, NTA_TAG_NET_RX_MISS_24)

/* 当前网卡对应的缓存不够了，当前缺少多少个缓存 */
#define NTA_TAG_NET_RX_NO_BUF_25 25
#define ADD_NET_NET_RX_NO_BUF(catche, value) \
    ADD_TV(catche, value, 8, NTA_TAG_NET_RX_NO_BUF_25)

/* tcp负载数据包含请求和应答，具体格式详情见：https://confluence.qingteng.cn/pages/viewpage.action?pageId=117053063
 * tcp_data字段的说明 */
#define NTA_TAG_TCP_DATA_26 26
#define ADD_TCP_DATA(catche, value, len) \
    ADD_U32_TLV(catche, value, len, NTA_TAG_TCP_DATA_26)

/* 设备ip */
#define NTA_TAG_DEVICE_IP_27 27
#define ADD_DEVICE_IP(catche) \
    ADD_TLV_PUBLIC(catche, device_ip, NTA_TAG_DEVICE_IP_27)

/* 一条udp连接在超时后，数据包的个数 */
#define NTA_TAG_UDP_PACKETS_28 28
#define ADD_UDP_PACKETS(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_UDP_PACKETS_28)

/* 一条tcp连接在超时后，syn包的个数 */
#define NTA_TAG_SYN_PACKETS_29 29
#define ADD_SYN_PACKETS(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_SYN_PACKETS_29)

/* 一条tcp连接在超时后，rst包的个数 */
#define NTA_TAG_RST_PACKETS_30 30
#define ADD_RST_PACKETS(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_RST_PACKETS_30)

/* 一条tcp连接在超时后，fin包的个数 */
#define NTA_TAG_FIN_PACKETS_31 31
#define ADD_FIN_PACKETS(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_FIN_PACKETS_31)

/* 一条tcp连接在超时后，ack包的个数 */
#define NTA_TAG_ACK_PACKETS_32 32
#define ADD_ACK_PACKETS(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_ACK_PACKETS_32)

/* 一条tcp连接在超时后，syn-ack包的个数 */
#define NTA_TAG_SYN_ACK_PACKETS_33 33
#define ADD_SYN_ACK_PACKETS(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_SYN_ACK_PACKETS_33)

/* 一条tcp连接在超时后，fin-ack包的个数 */
#define NTA_TAG_FIN_ACK_PACKETS_34 34
#define ADD_FIN_ACK_PACKETS(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_FIN_ACK_PACKETS_34)

/* 一条tcp连接在超时后，rst-ack包的个数 */
#define NTA_TAG_RST_ACK_PACKETS_35 35
#define ADD_RST_ACK_PACKETS(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_RST_ACK_PACKETS_35)

#define NTA_TAG_L7_CMDCODE_37 37
#define ADD_L7_CMDCODE(catche, value) \
    ADD_TV(catche, value, 2, NTA_TAG_L7_CMDCODE_37)

// #define NTA_TAG_USERINFO_38 38
// #define ADD_USERINFO(catche, value) \
//     ADD_TV(catche, value, 2, NTA_TAG_USERINFO_38)

/**/
// #define NTA_TAG_NETWORK_CARD_STATUS_39 39
// #define ADD_NETWORK_CARD_STATUS(catche, value) \
//     ADD_TV(catche, value, 2, NTA_TAG_NETWORK_CARD_STATUS_39)

/*与session_time组成一条连接的唯一标识*/
#define NTA_TAG_SESSION_ID_40 40
#define ADD_SESSION_ID(catche, value) \
    ADD_TV(catche, value, 2, NTA_TAG_SESSION_ID_40)

/*与session_id组成一条连接的唯一标识*/
#define NTA_TAG_SESSION_TIME_41 41
#define ADD_SESSION_TIME(catche, value) \
    ADD_TV(catche, value, 2, NTA_TAG_SESSION_TIME_41)

/////////////////////////////////////////////////////////////////////////////////

/* 告警信息相关字段 范围：1000-1999*/
/////////////////////////////////////////////////////////////////////////////////
/* http告警详情 */
#define NTA_TAG_HTTP_ALARM_1001 1001
#define ADD_HTTP_ALARM(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_HTTP_ALARM_1001)

/* 具体攻击技术 */
#define NTA_TAG_TECHNIQUES_1002 1002
#define ADD_TECHNIQUES(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_TECHNIQUES_1002)

/* 漏洞编号 */
#define NTA_TAG_CVE_1003 1003
#define ADD_CVE(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_CVE_1003)

/* 告警规则对应的评分 */
#define NTA_TAG_ALARM_SCORE_1004 1004
#define ADD_ALARM_SCORE(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_ALARM_SCORE_1004)

/* 入侵战术阶段 */
#define NTA_TAG_TACTICS_1005 1005
#define ADD_TACTICS(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_TACTICS_1005)

/* 二次检测信息详情 */
#define NTA_TAG_SECOND_DETECT_1006 1006
#define ADD_SECOND_DETECT(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_SECOND_DETECT_1006)

/* lua检测方法 */
#define NTA_TAG_LUA_DETECT_FUNCTION_1007 1007
#define ADD_LUA_DETECT_FUNCTION(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_LUA_DETECT_FUNCTION_1007)

/* 告警ID */
#define NTA_TAG_ALARM_ID_1008 1008
#define ADD_ALARM_ID(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_ALARM_ID_1008)

/* 攻击类型 */
#define NTA_TAG_ATTACK_TYPE_1009 1009
#define ADD_ATTACK_TYPE(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_ATTACK_TYPE_1009)

/* 危险等级 */
#define NTA_TAG_WARNING_LEVEL_1010 1010
#define ADD_WARNING_LEVEL(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_WARNING_LEVEL_1010)

/* lua检测方法返回值 */
#define NTA_TAG_LUA_RET_1011 1011
#define ADD_LUA_RET(catche, value) \
    ADD_TV(catche, value, 1, NTA_TAG_LUA_RET_1011)

/* 处置建议 */
#define NTA_TAG_SUGGEST_1012 1012
#define ADD_SUGGEST(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_SUGGEST_1012)

/////////////////////////////////////////////////////////////////////////////////
/* 邮件 范围：1100-1150*/
/////////////////////////////////////////////////////////////////////////////////
/* eml大小 */
#define NTA_TAG_EML_SIZE_1100 1100
#define ADD_EML_SIZE(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_EML_SIZE_1100)

/* 写入eml文件的大小 */
#define NTA_TAG_EML_FILESIZE_1101 1101
#define ADD_EML_FILESIZE(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_EML_FILESIZE_1101)

/* 写入eml文件失败的大小 */
#define NTA_TAG_EML_FAILED_FILESIZE_1102 1102
#define ADD_EML_FAILED_FILESIZE(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_EML_FAILED_FILESIZE_1102)

/* emlid */
#define NTA_TAG_EML_ID_1103 1103
#define ADD_EML_ID(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_EML_ID_1103)

/* eml文件开始偏移 */
#define NTA_TAG_EML_FILE_START_OFFSET_1104 1104
#define ADD_EML_FILE_START_OFFSET(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_EML_FILE_START_OFFSET_1104)

/* 写入eml文件的数量 */
#define NTA_TAG_EML_FILE_COUNT_1105 1105
#define ADD_EML_FILE_COUNT(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_EML_FILE_COUNT_1105)

/* eml文件状态 */
#define NTA_TAG_EML_STATUS_1106 1106
#define ADD_EML_STATUS(catche, value) \
    ADD_TV(catche, value, 2, NTA_TAG_EML_STATUS_1106)

/* eml 文件id */
#define NTA_TAG_EML_FILE_ID_1107 1107
#define ADD_EML_FILE_ID(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_EML_FILE_ID_1107)

/* eml文件路径 */
#define NTA_TAG_EML_FILE_PATH_1108 1108
#define ADD_EML_FILE_PATH(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_EML_FILE_PATH_1108)

/* 发件人 */
#define NTA_TAG_EML_FROM_1109 1109
#define ADD_EML_FROM(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_EML_FROM_1109)

/* 收件人 */
#define NTA_TAG_EML_TO_1110 1110
#define ADD_EML_TO(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_EML_TO_1110)

/* 抄送人 */
#define NTA_TAG_EML_CC_1111 1111
#define ADD_EML_CC(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_EML_CC_1111)

/* 主题 */
#define NTA_TAG_EML_SUBJECT_1112 1112
#define ADD_EML_SUBJECT(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_EML_SUBJECT_1112)

/* eml命令状态 */
#define NTA_TAG_EML_CMD_CODE_1113 1113
#define ADD_EML_CMD_CODE(catche, value) \
    ADD_TV(catche, value, 2, NTA_TAG_EML_CMD_CODE_1113)

/* eml是否中文邮件 */
#define NTA_TAG_EML_CHINESE_FLAG_1114 1114
#define ADD_EML_CHINESE_FLAG(catche, value) \
    ADD_TV(catche, value, 1, NTA_TAG_EML_CHINESE_FLAG_1114)

/* eml文件是否关闭标记 */
#define NTA_TAG_EML_FILE_CLOSE_FLAG_1115 1115
#define ADD_EML_FILE_CLOSE_FLAG(catche, value) \
    ADD_TV(catche, value, 1, NTA_TAG_EML_FILE_CLOSE_FLAG_1115)

/////////////////////////////////////////////////////////////////////////////////
/* 数据库 范围：1200-1300*/
/////////////////////////////////////////////////////////////////////////////////
/* 操作类型 */
#define NTA_TAG_DB_OP_CODE_1200 1200
#define ADD_DB_OP_CODE(catche, value) \
    ADD_TV(catche, value, 2, NTA_TAG_DB_OP_CODE_1200)

/*mysql协议连接版本*/
#define NTA_TAG_MYSQL_CON_VERSION_1201 1201
#define ADD_MYSQL_CON_VERSION(catche, value) \
    ADD_TV(catche, value, 1, NTA_TAG_MYSQL_CON_VERSION_1201)

/*mysql协议数据库版本*/
#define NTA_TAG_MYSQL_VERSION_1202 1202
#define ADD_MYSQL_VERSION(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_MYSQL_VERSION_1202)

/* 请求内容 */
#define NTA_TAG_DB_REQ_CONTEXT_1203 1203
#define ADD_DB_REQ_CONTEXT(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_DB_REQ_CONTEXT_1203)

/* 应答内容 */
#define NTA_TAG_FILEDS_COUNT_1204 1204
#define ADD_DB_FILEDS_COUNT(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_FILEDS_COUNT_1204)

/*catalog*/
#define NTA_TAG_DB_CATALOG_1205 1205
#define ADD_DB_CATALOG(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_DB_CATALOG_1205)

/*数据库名称*/
#define NTA_TAG_DB_DB_NAME_1206 1206
#define ADD_DB_DB_NAME(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_DB_DB_NAME_1206)

/*表名称*/
#define NTA_TAG_DB_TABLE_NAME_1207 1207
#define ADD_DB_TABLE_NAME(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_DB_TABLE_NAME_1207)

/*原始表名称*/
#define NTA_TAG_DB_ORG_TABLE_NAME_1208 1208
#define ADD_DB_ORG_TABLE_NAME(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_DB_ORG_TABLE_NAME_1208)

/*字段名称*/
#define NTA_TAG_DB_COLUMN_NAME_1209 1209
#define ADD_DB_COLUMN_NAME(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_DB_COLUMN_NAME_1209)

/*原始字段名称*/
#define NTA_TAG_DB_ORG_COLUMN_NAME_1210 1210
#define ADD_DB_ORG_COLUMN_NAME(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_DB_ORG_COLUMN_NAME_1210)

/*字段字符集设置*/
#define NTA_TAG_DB_CLOUMN_CHARACTER_SET_1211 1211
#define ADD_DB_CLOUMN_CHARACTER_SET(catche, value) \
    ADD_TV(catche, value, 2, NTA_TAG_DB_CLOUMN_CHARACTER_SET_1211)

/*字段类型*/
#define NTA_TAG_DB_FILED_TYPE_1212 1212
#define ADD_DB_FILED_TYPE(catche, value) \
    ADD_TV(catche, value, 1, NTA_TAG_DB_FILED_TYPE_1212)

/*结果集数量*/
#define NTA_TAG_DB_ROWS_COUNT_1213 1213
#define ADD_DB_ROWS_COUNT(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_DB_ROWS_COUNT_1213)

/*响应内容*/
#define NTA_TAG_DB_ROW_SET_1214 1214
#define ADD_DB_ROW_SET(catche, value, len) \
    ADD_U32_TLV(catche, value, len, NTA_TAG_DB_ROW_SET_1214)

/*数据结果集*/
#define NTA_TAG_DB_ROW_RESULTS_1215 1215
#define ADD_DB_ROW_RESULTS(catche, value) \
    ADD_TV(catche, value, 4, NTA_TAG_DB_ROW_RESULTS_1215)

/////////////////////////////////////////////////////////////////////////////////
/* DNS 范围：1400-1600*/
/////////////////////////////////////////////////////////////////////////////////

/* dns请求的域名 */
#define NTA_TAG_DNS_DOMAIN_NAME_1400 1400
#define ADD_DNS_DOMAIN_NAME(catche, value, len) \
    ADD_TLV(catche, value, len, NTA_TAG_DNS_DOMAIN_NAME_1400)

/* dns域名对应的ipv4 */
#define NTA_TAG_DNS_A_1401 1401
#define ADD_DNS_A(catche, value) ADD_TV(catche, value, 4, NTA_TAG_DNS_A_1401)

/* dns域名对应的ipv6 */
#define NTA_TAG_DNS_AAAA_1402 1402
#define ADD_DNS_AAAA(catche, value) \
    ADD_TV(catche, value, 16, NTA_TAG_DNS_AAAA_1402)

#endif /* __NTA_TAG_H__ */