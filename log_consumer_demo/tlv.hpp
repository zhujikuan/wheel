#ifndef __TLV_HPP__
#define __TLV_HPP__
#include "tag.h"

#define SET_TLV_FIELD(field, t, l, v) \
    do                                \
    {                                 \
        field.m_tag   = (t);          \
        field.m_value = (v);          \
        field.m_len   = (l);          \
    } while (0);

#define OFFSET_OVERFLOWS(offset, len) \
    do                                \
    {                                 \
        if ((offset) > (len))         \
        {                             \
            goto RET_ERROR;           \
        }                             \
    } while (0);

#define SET_TV_MEMBER(m, t, l, p, pl, o) \
    do                                   \
    {                                    \
        SET_TLV_FIELD(m, t, l, p + o);   \
        o += l;                          \
        OFFSET_OVERFLOWS(o, pl);         \
    } while (0);

#define SET_TLV_MEMBER(m, t, l, p, pl, o) \
    do                                    \
    {                                     \
        o += sizeof(unsigned short);      \
        OFFSET_OVERFLOWS(o, pl);          \
        SET_TLV_FIELD(m, t, l, p + o);    \
        o += l;                           \
        OFFSET_OVERFLOWS(o, pl);          \
    } while (0);

class tlv_field_info
{
 private:
    /* data */
 public:
    tlv_field_info(/* args */)
    {
        m_new   = false;
        m_tag   = 0;
        m_len   = 0;
        m_value = NULL;
    }
    ~tlv_field_info()
    {
        if (m_new)
        {
            delete[] m_value;
        }
    }
    void reset()
    {
        if (m_new)
        {
            delete[] m_value;
        }
        m_value = NULL;
        m_new   = false;
        m_tag   = 0;
        m_len   = 0;
    }
    bool m_new;
    unsigned short m_tag;
    unsigned short m_len;
    unsigned char *m_value;
};

// typedef struct
// {
//     unsigned short tag;
//     unsigned short len;
// }tlv_hd_t;

#define ADD_TV_U64(catche, offset, tag, value)           \
    do                                                   \
    {                                                    \
        *(unsigned short *)(catche + offset) = tag;      \
        offset += sizeof(unsigned short);                \
        *(unsigned long int *)(catche + offset) = value; \
        offset += sizeof(unsigned long int);             \
    } while (0);

#define ADD_TV_U32(catche, offset, tag, value)      \
    do                                              \
    {                                               \
        *(unsigned short *)(catche + offset) = tag; \
        offset += sizeof(unsigned short);           \
        *(unsigned int *)(catche + offset) = value; \
        offset += sizeof(unsigned int);             \
    } while (0);

#define ADD_TV_U16(catche, offset, tag, value)        \
    do                                                \
    {                                                 \
        *(unsigned short *)(catche + offset) = tag;   \
        offset += sizeof(unsigned short);             \
        *(unsigned short *)(catche + offset) = value; \
        offset += sizeof(unsigned short);             \
    } while (0);

#define ADD_TV_LEN(catche, offset, tag, value, len) \
    do                                              \
    {                                               \
        *(unsigned short *)(catche + offset) = tag; \
        offset += sizeof(unsigned short);           \
        memcpy(catche + offset, value, len);        \
        offset += len;                              \
    } while (0);

#define ADD_TLV_2BYTE(catche, offset, tag, value, len) \
    do                                                 \
    {                                                  \
        *(unsigned short *)(catche + offset) = tag;    \
        offset += sizeof(unsigned short);              \
        *(unsigned short *)(catche + offset) = len;    \
        offset += sizeof(unsigned short);              \
        memcpy(catche + offset, value, len);           \
        offset += len;                                 \
    } while (0);

class public_tuple
{
 private:
    /* data */
 public:
    public_tuple(/* args */);
    ~public_tuple();

    tlv_field_info m_ts;

    tlv_field_info m_sip46;
    tlv_field_info m_dip46;

    tlv_field_info m_sport;
    tlv_field_info m_dport;

    tlv_field_info m_device_id;
    tlv_field_info m_device_ip;
    tlv_field_info m_company_id;
};

#endif  //__TLV_HPP__
