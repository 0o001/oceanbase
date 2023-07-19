// Copyright (c) 2022-present Oceanbase Inc. All Rights Reserved.
// Author:
//   suzhi.yt <>

#pragma once

#include "storage/direct_load/ob_direct_load_external_fragment.h"
#include "storage/direct_load/ob_direct_load_i_table.h"

namespace oceanbase
{
namespace storage
{

struct ObDirectLoadExternalTableCreateParam
{
public:
  ObDirectLoadExternalTableCreateParam();
  ~ObDirectLoadExternalTableCreateParam();
  bool is_valid() const;
  TO_STRING_KV(K_(tablet_id), K_(data_block_size), K_(row_count), K_(max_data_block_size),
               K_(fragments));
public:
  common::ObTabletID tablet_id_;
  int64_t data_block_size_;
  int64_t row_count_;
  int64_t max_data_block_size_;
  ObDirectLoadExternalFragmentArray fragments_;
};

struct ObDirectLoadExternalTableMeta
{
public:
  ObDirectLoadExternalTableMeta();
  ~ObDirectLoadExternalTableMeta();
  void reset();
  TO_STRING_KV(K_(tablet_id), K_(data_block_size), K_(row_count), K_(max_data_block_size));
public:
  common::ObTabletID tablet_id_;
  int64_t data_block_size_;
  int64_t row_count_;
  int64_t max_data_block_size_;
};

class ObDirectLoadExternalTable : public ObIDirectLoadPartitionTable
{
public:
  ObDirectLoadExternalTable();
  virtual ~ObDirectLoadExternalTable();
  void reset();
  int init(const ObDirectLoadExternalTableCreateParam &param);
  const common::ObTabletID &get_tablet_id() const override { return meta_.tablet_id_; }
  int64_t get_row_count() const override { return meta_.row_count_; }
  bool is_valid() const override { return is_inited_; }
  int copy(const ObDirectLoadExternalTable &other);
  const ObDirectLoadExternalTableMeta &get_meta() const { return meta_; }
  const ObDirectLoadExternalFragmentArray &get_fragments() const { return fragments_; }
  TO_STRING_KV(K_(meta), K_(fragments));
private:
  ObDirectLoadExternalTableMeta meta_;
  ObDirectLoadExternalFragmentArray fragments_;
  bool is_inited_;
  DISABLE_COPY_ASSIGN(ObDirectLoadExternalTable);
};

} // namespace storage
} // namespace oceanbase