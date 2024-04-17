	.text
	.file	"test.c"
	.globl	test_rand                       ; -- Begin function test_rand
	.type	test_rand,@function
test_rand:                              ; @test_rand
; %bb.0:                                ; %entry
	addi	x2, x2, -24
	sd	x1, 16(x2)                      ; 8-byte Folded Spill
	sd	x8, 8(x2)                       ; 8-byte Folded Spill
	addi	x8, x2, 24
	andi	x2, x2, -8
	sd	x10, 0(x2)
	ld	x10, 0(x2)
	rand	x10
	addi	x2, x8, -24
	ld	x8, 8(x2)                       ; 8-byte Folded Reload
	ld	x1, 16(x2)                      ; 8-byte Folded Reload
	addi	x2, x2, 24
	jalr	x0, 0(x1)
.Lfunc_end0:
	.size	test_rand, .Lfunc_end0-test_rand
                                        ; -- End function
	.globl	test_get_frame                  ; -- Begin function test_get_frame
	.type	test_get_frame,@function
test_get_frame:                         ; @test_get_frame
; %bb.0:                                ; %entry
	addi	x2, x2, -16
	sd	x1, 8(x2)                       ; 8-byte Folded Spill
	sd	x8, 0(x2)                       ; 8-byte Folded Spill
	addi	x8, x2, 16
	gf	x10
	ld	x8, 0(x2)                       ; 8-byte Folded Reload
	ld	x1, 8(x2)                       ; 8-byte Folded Reload
	addi	x2, x2, 16
	jalr	x0, 0(x1)
.Lfunc_end1:
	.size	test_get_frame, .Lfunc_end1-test_get_frame
                                        ; -- End function
	.globl	test_flush                      ; -- Begin function test_flush
	.type	test_flush,@function
test_flush:                             ; @test_flush
; %bb.0:                                ; %entry
	addi	x2, x2, -16
	sd	x1, 8(x2)                       ; 8-byte Folded Spill
	sd	x8, 0(x2)                       ; 8-byte Folded Spill
	addi	x8, x2, 16
	flush	
	ld	x8, 0(x2)                       ; 8-byte Folded Reload
	ld	x1, 8(x2)                       ; 8-byte Folded Reload
	addi	x2, x2, 16
	jalr	x0, 0(x1)
.Lfunc_end2:
	.size	test_flush, .Lfunc_end2-test_flush
                                        ; -- End function
	.globl	test_call                       ; -- Begin function test_call
	.type	test_call,@function
test_call:                              ; @test_call
; %bb.0:                                ; %entry
	addi	x2, x2, -32
	sd	x1, 24(x2)                      ; 8-byte Folded Spill
	sd	x8, 16(x2)                      ; 8-byte Folded Spill
	addi	x8, x2, 32
	andi	x2, x2, -8
	sd	x10, 8(x2)
	addi	x10, x0, 2
	sd	x10, 0(x2)
	ld	x10, 8(x2)
	ld	x11, 0(x2)
	add	x10, x10, x11
	call	test_rand
	addi	x10, x10, 7
	addi	x2, x8, -32
	ld	x8, 16(x2)                      ; 8-byte Folded Reload
	ld	x1, 24(x2)                      ; 8-byte Folded Reload
	addi	x2, x2, 32
	jalr	x0, 0(x1)
.Lfunc_end3:
	.size	test_call, .Lfunc_end3-test_call
                                        ; -- End function
	.globl	test_control_flow               ; -- Begin function test_control_flow
	.type	test_control_flow,@function
test_control_flow:                      ; @test_control_flow
; %bb.0:                                ; %entry
	addi	x2, x2, -40
	sd	x1, 32(x2)                      ; 8-byte Folded Spill
	sd	x8, 24(x2)                      ; 8-byte Folded Spill
	addi	x8, x2, 40
	andi	x2, x2, -8
	sd	x10, 16(x2)
	sd	x11, 8(x2)
	addi	x10, x0, 1
	sd	x10, 0(x2)
	ld	x10, 16(x2)
	ld	x11, 8(x2)
	beq	x10, x11, .LBB4_2
	jal	x0, .LBB4_1
.LBB4_1:                                ; %if.then
	ld	x10, 16(x2)
	ld	x11, 8(x2)
	mul	x10, x10, x11
	sd	x10, 0(x2)
	jal	x0, .LBB4_3
.LBB4_2:                                ; %if.else
	ld	x10, 16(x2)
	addi	x10, x10, 10
	sd	x10, 16(x2)
	ld	x10, 16(x2)
	ld	x11, 8(x2)
	div	x10, x10, x11
	ld	x11, 0(x2)
	add	x10, x11, x10
	sd	x10, 0(x2)
	jal	x0, .LBB4_3
.LBB4_3:                                ; %if.end
	ld	x10, 0(x2)
	mul	x11, x10, x10
	sub	x10, x11, x10
	addi	x2, x8, -40
	ld	x8, 24(x2)                      ; 8-byte Folded Reload
	ld	x1, 32(x2)                      ; 8-byte Folded Reload
	addi	x2, x2, 40
	jalr	x0, 0(x1)
.Lfunc_end4:
	.size	test_control_flow, .Lfunc_end4-test_control_flow
                                        ; -- End function
	.globl	test_imm_minus                  ; -- Begin function test_imm_minus
	.type	test_imm_minus,@function
test_imm_minus:                         ; @test_imm_minus
; %bb.0:                                ; %entry
	addi	x2, x2, -24
	sd	x1, 16(x2)                      ; 8-byte Folded Spill
	sd	x8, 8(x2)                       ; 8-byte Folded Spill
	addi	x8, x2, 24
	sw	x10, -20(x8)
	addi	x10, x0, 1
	sw	x10, -24(x8)
	lw	x10, -24(x8)
	sub	x10, x0, x10
	ld	x8, 8(x2)                       ; 8-byte Folded Reload
	ld	x1, 16(x2)                      ; 8-byte Folded Reload
	addi	x2, x2, 24
	jalr	x0, 0(x1)
.Lfunc_end5:
	.size	test_imm_minus, .Lfunc_end5-test_imm_minus
                                        ; -- End function
	.globl	test_for_sum                    ; -- Begin function test_for_sum
	.type	test_for_sum,@function
test_for_sum:                           ; @test_for_sum
; %bb.0:                                ; %entry
	addi	x2, x2, -32
	sd	x1, 24(x2)                      ; 8-byte Folded Spill
	sd	x8, 16(x2)                      ; 8-byte Folded Spill
	addi	x8, x2, 32
	andi	x2, x2, -8
	sd	x10, 8(x2)
	sd	x0, 0(x2)
	jal	x0, .LBB6_1
.LBB6_1:                                ; %while.cond
                                        ; =>This Inner Loop Header: Depth=1
	ld	x10, 8(x2)
	beq	x10, x0, .LBB6_3
	jal	x0, .LBB6_2
.LBB6_2:                                ; %while.body
                                        ;   in Loop: Header=BB6_1 Depth=1
	ld	x10, 8(x2)
	ld	x11, 0(x2)
	add	x10, x11, x10
	sd	x10, 0(x2)
	ld	x10, 8(x2)
	addi	x10, x10, -1
	sd	x10, 8(x2)
	jal	x0, .LBB6_1
.LBB6_3:                                ; %while.end
	ld	x10, 0(x2)
	addi	x2, x8, -32
	ld	x8, 16(x2)                      ; 8-byte Folded Reload
	ld	x1, 24(x2)                      ; 8-byte Folded Reload
	addi	x2, x2, 32
	jalr	x0, 0(x1)
.Lfunc_end6:
	.size	test_for_sum, .Lfunc_end6-test_for_sum
                                        ; -- End function
	.globl	test_for_for                    ; -- Begin function test_for_for
	.type	test_for_for,@function
test_for_for:                           ; @test_for_for
; %bb.0:                                ; %entry
	addi	x2, x2, -40
	sd	x1, 32(x2)                      ; 8-byte Folded Spill
	sd	x8, 24(x2)                      ; 8-byte Folded Spill
	addi	x8, x2, 40
	andi	x2, x2, -8
	sd	x10, 16(x2)
	sd	x11, 8(x2)
	sd	x0, 0(x2)
	jal	x0, .LBB7_1
.LBB7_1:                                ; %while.cond
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB7_3 Depth 2
	ld	x10, 16(x2)
	beq	x10, x0, .LBB7_6
	jal	x0, .LBB7_2
.LBB7_2:                                ; %while.body
                                        ;   in Loop: Header=BB7_1 Depth=1
	jal	x0, .LBB7_3
.LBB7_3:                                ; %while.cond1
                                        ;   Parent Loop BB7_1 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ld	x10, 8(x2)
	beq	x10, x0, .LBB7_5
	jal	x0, .LBB7_4
.LBB7_4:                                ; %while.body3
                                        ;   in Loop: Header=BB7_3 Depth=2
	ld	x10, 8(x2)
	ld	x11, 16(x2)
	mul	x10, x10, x11
	ld	x11, 0(x2)
	add	x10, x11, x10
	sd	x10, 0(x2)
	ld	x10, 8(x2)
	addi	x10, x10, -1
	sd	x10, 8(x2)
	jal	x0, .LBB7_3
.LBB7_5:                                ; %while.end
                                        ;   in Loop: Header=BB7_1 Depth=1
	ld	x10, 16(x2)
	addi	x10, x10, -1
	sd	x10, 16(x2)
	jal	x0, .LBB7_1
.LBB7_6:                                ; %while.end5
	ld	x10, 0(x2)
	addi	x2, x8, -40
	ld	x8, 24(x2)                      ; 8-byte Folded Reload
	ld	x1, 32(x2)                      ; 8-byte Folded Reload
	addi	x2, x2, 40
	jalr	x0, 0(x1)
.Lfunc_end7:
	.size	test_for_for, .Lfunc_end7-test_for_for
                                        ; -- End function
	.globl	test_imm_div                    ; -- Begin function test_imm_div
	.type	test_imm_div,@function
test_imm_div:                           ; @test_imm_div
; %bb.0:                                ; %entry
	addi	x2, x2, -24
	sd	x1, 16(x2)                      ; 8-byte Folded Spill
	sd	x8, 8(x2)                       ; 8-byte Folded Spill
	addi	x8, x2, 24
	andi	x2, x2, -8
	sd	x10, 0(x2)
	ld	x10, 0(x2)
	lui	x11, 2
	addi	x11, x11, 808
	div	x10, x10, x11
	addi	x2, x8, -24
	ld	x8, 8(x2)                       ; 8-byte Folded Reload
	ld	x1, 16(x2)                      ; 8-byte Folded Reload
	addi	x2, x2, 24
	jalr	x0, 0(x1)
.Lfunc_end8:
	.size	test_imm_div, .Lfunc_end8-test_imm_div
                                        ; -- End function
	.globl	test_int_vals                   ; -- Begin function test_int_vals
	.type	test_int_vals,@function
test_int_vals:                          ; @test_int_vals
; %bb.0:                                ; %entry
	addi	x2, x2, -40
	sd	x1, 32(x2)                      ; 8-byte Folded Spill
	sd	x8, 24(x2)                      ; 8-byte Folded Spill
	addi	x8, x2, 40
	andi	x2, x2, -8
	sw	x10, 20(x2)
	sd	x11, 8(x2)
	ld	x10, 8(x2)
	sw	x10, 4(x2)
	lw	x10, 4(x2)
	mul	x10, x10, x10
	sw	x10, 0(x2)
	ld	x10, 8(x2)
	lw	x11, 20(x2)
	div	x10, x10, x11
	add	x10, x10, x11
	lw	x11, 0(x2)
	sub	x10, x10, x11
	addi	x2, x8, -40
	ld	x8, 24(x2)                      ; 8-byte Folded Reload
	ld	x1, 32(x2)                      ; 8-byte Folded Reload
	addi	x2, x2, 40
	jalr	x0, 0(x1)
.Lfunc_end9:
	.size	test_int_vals, .Lfunc_end9-test_int_vals
                                        ; -- End function
	.ident	"clang version 19.0.0git (https://github.com/Vokerlee/llvm-project-grisc-v.git aeb41931c739f22db142805825a4885eee96746a)"
	.section	".note.GNU-stack","",@progbits
