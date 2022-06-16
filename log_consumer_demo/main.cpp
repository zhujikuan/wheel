#include <librdkafka/rdkafka.h>
#include <stdio.h>

#include <iostream>

#include "nta_tag.h"
#include "tlv.hpp"

#define NTA_TAG_START_TIME_11_TVLEN (2 + 8)
#define NTA_TAG_END_TIME_12_TVLEN (2 + 8)
#define NTA_TAG_DIP4_5_TVLEN (2 + 4)
#define NTA_TAG_DIP6_6_TVLEN (2 + 16)
#define NTA_TAG_DPORT_8_TVLEN (2 + 2)
#define NTA_TAG_L4_PROTOCOL_13_TVLEN (2 + 2)
#define NTA_TAG_L7_PROTOCOL_14_TVLEN (2 + 2)
#define NTA_TAG_ALARM_ID_1008_TLVLEN(len) (2 + 2 + len)
#define NTA_TAG_DEVICE_ID_1_TLVLEN(len) (2 + 2 + len)
#define NTA_TAG_DEVICE_IP_27_TLVLEN(len) (2 + 2 + len)
#define NTA_TAG_COMPANY_ID_2_TLVLEN(len) (2 + 2 + len)

#define NTA_TAG_SESSION_ID_40_TVLEN (2 + 8)
#define NTA_TAG_SESSION_TIME_41_TVLEN (2 + 8)
#define NTA_TAG_SIP4_3_TVLEN (2 + 4)
#define NTA_TAG_SIP6_4_TVLEN (2 + 16)
#define NTA_TAG_SPORT_7_TVLEN (2 + 2)
#define NTA_TAG_ACCOUNT_NAME_15_TLVLEN(len) (2 + 2 + len)
#define NTA_TAG_ACCOUNT_PASSWORD_16_TLVLEN(len) (2 + +2 + len)

void ipv4_b2bd(char *ip4) {
    unsigned char *tmp = (unsigned char *)ip4;
    printf("%d.%d.%d.%d", tmp[0], tmp[1], tmp[2], tmp[3]);
}
void ipv6_b2bd(char *ip6) {}
bool analyse_log(char *payload, int payload_len) {
    int offset = 0;

    while (offset < payload_len) {
        unsigned short *tlv_hd = (unsigned short *)(payload + offset);
        // offset += sizeof(unsigned short);
        OFFSET_OVERFLOWS(offset, payload_len);
        switch (tlv_hd[0]) {
            case NTA_TAG_START_TIME_11:
                printf("start time: %ld\n",
                       *(unsigned long *)(payload + offset + 2));
                offset += NTA_TAG_START_TIME_11_TVLEN;
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_END_TIME_12:
                printf("end time: %ld\n",
                       *(unsigned long *)(payload + offset + 2));
                offset += NTA_TAG_END_TIME_12_TVLEN;
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_DIP4_5:
                printf("dest ipv4: ");
                ipv4_b2bd(payload + offset + 2);
                printf("\n");
                offset += NTA_TAG_DIP4_5_TVLEN;
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_DIP6_6:
                printf("ipv6: ");
                ipv6_b2bd(payload + offset + 2);
                printf("\n");
                offset += NTA_TAG_DIP6_6_TVLEN;
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_DPORT_8:
                printf("dport: %d", *(unsigned short *)(payload + offset + 2));
                offset += NTA_TAG_DPORT_8_TVLEN;
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_L4_PROTOCOL_13:
                printf("l4_protocol: %d",
                       *(unsigned short *)(payload + offset + 2));
                offset += NTA_TAG_L4_PROTOCOL_13_TVLEN;
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_L7_PROTOCOL_14:
                printf("l7_protocol: %d",
                       *(unsigned short *)(payload + offset + 2));

                offset += NTA_TAG_L7_PROTOCOL_14_TVLEN;
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_ALARM_ID_1008:
                tlv_hd[1];
                printf("alarm_id[%d]: %s\n", tlv_hd[1],
                       payload + offset + tlv_hd[1] + 2);
                offset += NTA_TAG_ALARM_ID_1008_TLVLEN(tlv_hd[1]);
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_SESSION_ID_40:
                printf("session_id: %ld\n",
                       *(unsigned long *)(payload + offset + 2));
                offset += NTA_TAG_SESSION_ID_40_TVLEN;

                break;
            case NTA_TAG_SESSION_TIME_41:
                printf("session_time: %ld\n",
                       *(unsigned long *)(payload + offset + 2));
                offset += NTA_TAG_SESSION_TIME_41_TVLEN;
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_SIP4_3:
                printf("source ipv4: ");
                ipv4_b2bd(payload + offset + 2);
                printf("\n");
                offset += NTA_TAG_SIP4_3_TVLEN;
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_SIP6_4:
                printf("ipv6: ");
                ipv6_b2bd(payload + offset + 2);
                printf("\n");
                offset += NTA_TAG_SIP6_4_TVLEN;
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_SPORT_7:
                printf("sport: %d\n",
                       *(unsigned short *)(payload + offset + 2));
                offset += NTA_TAG_SPORT_7_TVLEN;
                OFFSET_OVERFLOWS(offset, payload_len);
                break;

            case NTA_TAG_ACCOUNT_NAME_15:
                printf("name: [%d] :%s", tlv_hd[1], (payload + offset + 2));
                offset += NTA_TAG_ACCOUNT_NAME_15_TLVLEN(tlv_hd[1]);
                OFFSET_OVERFLOWS(offset, payload_len);
                break;

            case NTA_TAG_ACCOUNT_PASSWORD_16:
                printf("name: [%d] :%s", tlv_hd[1], (payload + offset + 2));
                offset += NTA_TAG_ACCOUNT_PASSWORD_16_TLVLEN(tlv_hd[1]);
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_DEVICE_ID_1:
                printf("device id: [%d] :%s", tlv_hd[1],
                       (payload + offset + 2));
                offset += NTA_TAG_DEVICE_ID_1_TLVLEN(tlv_hd[1]);
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_DEVICE_IP_27:
                printf("device ip: [%d] :%s", tlv_hd[1],
                       (payload + offset + 2));
                offset += NTA_TAG_DEVICE_IP_27_TLVLEN(tlv_hd[1]);
                OFFSET_OVERFLOWS(offset, payload_len);
                break;
            case NTA_TAG_COMPANY_ID_2:
                printf("company id: [%d] :%s", tlv_hd[1],
                       (payload + offset + 2));
                offset += NTA_TAG_COMPANY_ID_2_TLVLEN(tlv_hd[1]);
                OFFSET_OVERFLOWS(offset, payload_len);
                break;

            default:
                std::cout << "default" << std::endl;
                goto RET_ERROR;
        }
    }
RET_ERROR:
    std::cout << "analyse failed" << std::endl;

    return true;
}
static int run_consumer() {
    rd_kafka_conf_t *conf = rd_kafka_conf_new();
    rd_kafka_t *rk;
    char errstr[512];
    rd_kafka_resp_err_t err;
    rd_kafka_topic_partition_list_t *topics;
    int i;

    // rd_kafka_conf_set(conf, "group.id", "qt_v01", NULL, 0);

    /* If there is no committed offset for this group, start reading
     * partitions from the beginning. */
    rd_kafka_conf_set(conf, "auto.offset.reset", "earliest", NULL, 0);

    /* Disable ERR__PARTITION_EOF when reaching end of partition. */
    rd_kafka_conf_set(conf, "enable.partition.eof", "false", NULL, 0);

    rd_kafka_conf_set(conf, "bootstrap.servers", "127.0.0.1:9092", NULL, 0);
    rd_kafka_conf_set(conf, "group.id", "qt_v01", NULL, 0);

    /* Create consumer.
     * A successful call assumes ownership of \p conf. */
    rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf, errstr, sizeof(errstr));
    if (!rk) {
        fprintf(stderr, "Failed to create consumer: %s\n", errstr);
        rd_kafka_conf_destroy(conf);
        return -1;
    }

    /* Redirect all (present and future) partition message queues to the
     * main consumer queue so that they can all be consumed from the
     * same consumer_poll() call. */
    rd_kafka_poll_set_consumer(rk);

    /* Create subscription list.
     * The partition will be ignored by subscribe() */
    topics = rd_kafka_topic_partition_list_new(1);
    rd_kafka_topic_partition_list_add(topics, "http_alarm",
                                      RD_KAFKA_PARTITION_UA);

    /* Subscribe to topic(s) */
    fprintf(stderr,
            "Subscribed to %s, waiting for assignment and messages...\n"
            "Press Ctrl-C to exit.\n",
            "http_alarm");

    err = rd_kafka_subscribe(rk, topics);
    rd_kafka_topic_partition_list_destroy(topics);

    if (err) {
        fprintf(stderr, "Subscribe(%s) failed: %s\n", "http_alarm",
                rd_kafka_err2str(err));
        rd_kafka_destroy(rk);
        return -1;
    }

    /* Consume messages */
    while (1) {
        rd_kafka_message_t *rkm;

        /* Poll for a single message or an error event.
         * Use a finite timeout so that Ctrl-C (run==0) is honoured. */
        rkm = rd_kafka_consumer_poll(rk, 1000);
        if (!rkm) continue;

        if (rkm->err) {
            /* Consumer error: typically just informational. */
            fprintf(stderr, "Consumer error: %s\n",
                    rd_kafka_message_errstr(rkm));
        } else {
            /* Proper message */
            fprintf(stderr,
                    "Received message on %s [%d] "
                    "at offset %" PRId64 ": %.*s\n",
                    rd_kafka_topic_name(rkm->rkt), (int)rkm->partition,
                    rkm->offset, (int)rkm->len, (const char *)rkm->payload);
            // handle_message(rkm);

            printf("recv[%ld]\n", rkm->len);
            analyse_log((char *)rkm->payload, rkm->len);
        }

        rd_kafka_message_destroy(rkm);
    }

    /* Close the consumer to have it gracefully leave the consumer group
     * and commit final offsets. */
    rd_kafka_consumer_close(rk);

    /* Destroy the consumer instance. */
    rd_kafka_destroy(rk);

    return 0;
}
int main(int argc, char **argv) {
    run_consumer();

    return 0;
}
