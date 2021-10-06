define(`H5VL_LOG_TIMERS', `( `H5VL_log_file_create', dnl
                            `H5VL_log_file_create_init', dnl
                            `H5VL_log_file_create_file', dnl
                            `H5VL_log_file_create_group', dnl
                            `H5VL_log_file_create_fh', dnl
                            `H5VL_log_file_create_stripe', dnl
                            `H5VL_log_file_create_group_rank', dnl
                            `H5VL_log_file_create_subfile', dnl
                            `H5VL_log_file_open', dnl
                            `H5VL_log_file_get', dnl
                            `H5VL_log_file_specific', dnl
                            `H5VL_log_file_optional', dnl
                            `H5VL_log_file_close', dnl
                            `H5VL_log_group_create', dnl
                            `H5VL_log_group_open', dnl
                            `H5VL_log_group_get', dnl
                            `H5VL_log_group_specific', dnl
                            `H5VL_log_group_optional', dnl
                            `H5VL_log_group_close', dnl
                            `H5VL_log_att_create', dnl
                            `H5VL_log_att_open', dnl
                            `H5VL_log_att_read', dnl
                            `H5VL_log_att_write', dnl
                            `H5VL_log_att_get', dnl
                            `H5VL_log_att_specific', dnl
                            `H5VL_log_att_optional', dnl
                            `H5VL_log_att_close', dnl
                            `H5VL_log_dataset_create', dnl
                            `H5VL_log_dataset_open', dnl
                            `H5VL_log_dataset_read', dnl
                            `H5VL_log_dataset_read_init', dnl
                            `H5VL_log_dataset_write', dnl
                            `H5VL_log_dataset_write_init', dnl
                            `H5VL_log_dataset_write_start_count', dnl
                            `H5VL_log_dataset_write_encode', dnl
                            `H5VL_log_dataset_write_meta_deflate', dnl
                            `H5VL_log_dataset_write_pack', dnl
                            `H5VL_log_dataset_write_convert', dnl
                            `H5VL_log_dataset_write_filter', dnl
                            `H5VL_log_dataset_write_finalize', dnl
                            `H5VL_log_dataset_get', dnl
                            `H5VL_log_dataset_specific', dnl
                            `H5VL_log_dataset_optional', dnl
                            `H5VL_log_dataset_close', dnl
                            `H5VLfile_create', dnl
                            `H5VLfile_open', dnl
                            `H5VLfile_get', dnl
                            `H5VLfile_specific', dnl
                            `H5VLfile_optional', dnl
                            `H5VLfile_close', dnl
                            `H5VLgroup_create', dnl
                            `H5VLgroup_open', dnl
                            `H5VLgroup_get', dnl
                            `H5VLgroup_specific', dnl
                            `H5VLgroup_optional', dnl
                            `H5VLgroup_close', dnl
                            `H5VLatt_create', dnl
                            `H5VLatt_open', dnl
                            `H5VLatt_read', dnl
                            `H5VLatt_write', dnl
                            `H5VLatt_get', dnl
                            `H5VLatt_specific', dnl
                            `H5VLatt_optional', dnl
                            `H5VLatt_close', dnl
                            `H5VLdataset_create', dnl
                            `H5VLdataset_open', dnl
                            `H5VLdataset_read', dnl
                            `H5VLdataset_write', dnl
                            `H5VLdataset_get', dnl
                            `H5VLdataset_specific', dnl
                            `H5VLdataset_optional', dnl
                            `H5VLdataset_close', dnl
                            `H5VL_log_filei_flush', dnl
                            `H5VL_log_filei_metaflush', dnl
                            `H5VL_log_filei_metaflush_init', dnl
                            `H5VL_log_filei_metaflush_hash', dnl
                            `H5VL_log_filei_metaflush_pack', dnl
                            `H5VL_log_filei_metaflush_zip', dnl
                            `H5VL_log_filei_metaflush_sync', dnl
                            `H5VL_log_filei_metaflush_create', dnl
                            `H5VL_log_filei_metaflush_write', dnl
                            `H5VL_log_filei_metaflush_close', dnl
                            `H5VL_log_filei_metaflush_barrier', dnl
                            `H5VL_log_filei_metaflush_finalize', dnl
                            `H5VL_log_filei_metaflush_size', dnl
                            `H5VL_log_filei_metaflush_size_dedup', dnl
                            `H5VL_log_filei_metaflush_size_zip', dnl
                            `H5VL_log_filei_metaflush_repeat_count', dnl
                            `H5VL_log_filei_metaupdate', dnl
                            `H5VL_log_dataseti_readi_gen_rtypes', dnl
                            `H5VL_log_dataseti_open_with_uo', dnl
                            `H5VL_log_dataseti_wrap', dnl
                            `H5VL_logi_get_dataspace_sel_type', dnl
                            `H5VL_logi_get_dataspace_selection', dnl
                            `H5VL_log_nb_flush_read_reqs', dnl
                            `H5VL_log_nb_flush_write_reqs', dnl
                            `H5VL_log_nb_flush_write_reqs_init', dnl
                            `H5VL_log_nb_flush_write_reqs_sync', dnl
                            `H5VL_log_nb_flush_write_reqs_create', dnl
                            `H5VL_log_nb_flush_write_reqs_wr', dnl
                            `H5VL_log_nb_flush_write_reqs_create_virtual', dnl
                            `H5VL_log_nb_write_reqs_aligned', dnl
                            `H5VL_log_nb_flush_write_reqs_size', dnl
)')`'dnl


